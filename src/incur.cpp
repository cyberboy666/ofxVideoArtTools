#include "incur.h"

void incur::setupThis(string mapPath){
    #ifdef TARGET_RASPBERRY_PI
    consoleListener.setup(this);
    lastAnalogReading = {0, 0, 0, 0, 0, 0, 0, 0};
    adcDelay = 0.1; 
    isAnalogListening = false;
    #else
    isAnalogListening = false;
    #endif
    lastGetTime = ofGetElapsedTimef();
    lastButtonTime = ofGetElapsedTimef();
    isKeyListening = true;
    keyActions = {};
    isMidiListening = false;
    midiIgnoreCcOff = false;
    midiActions = {};
    isOscListening = false;
    analogActions = {};
    bool parsingSuccessful = result.open(mapPath);
}

bool incur::midiListening(bool ignoreCcOff){
    midiIn.listInPorts();
    if(midiIn.getNumInPorts() < 2){
    ofLog() << "no external midi device attached";
    return false;
    }
    midiIn.openPort(1);
    midiIn.addListener(this);
    isMidiListening = midiIn.isOpen();
    midiIgnoreCcOff = ignoreCcOff;
    return isMidiListening;
}

bool incur::oscListening(){
    receiver.setup(8000);
    isOscListening = true;
    return isOscListening;
}

bool incur::analogListening(){
    if(!isAnalogListening){
        return false;
    }
#ifdef TARGET_RASPBERRY_PI
    else{
        a2d0.setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
        a2d1.setup("/dev/spidev0.1", SPI_MODE_0, 1000000, 8);

        gpio4.setup(GPIO4, IN, HIGH);
        gpio5.setup(GPIO5, IN, HIGH);
        gpio6.setup(GPIO6, IN, HIGH);
        gpio7.setup(GPIO7, IN, HIGH);
        gpio9.setup(GPIO9, IN, HIGH);
        gpio12.setup(GPIO12, IN, HIGH);
        gpio13.setup(GPIO13, IN, HIGH);
        gpio18.setup(GPIO18, IN, HIGH);
        gpio19.setup(GPIO19, IN, HIGH);
        gpio22.setup(GPIO22, IN, HIGH);
        gpio23.setup(GPIO23, IN, HIGH);

        gpioList = {gpio4, gpio5, gpio6, gpio7, gpio9, gpio12, gpio13, gpio18, gpio19, gpio22, gpio23};

        return isAnalogListening;
    }
#endif
    return false;
}

vector<vector<string>> incur::getActions(){
    vector<vector<string>> actionsList;

    if(isKeyListening){
        actionsList.insert(actionsList.end(), keyActions.begin(), keyActions.end());
        keyActions.clear();
    }
    if(isMidiListening){
        actionsList.insert(actionsList.end(), midiActions.begin(), midiActions.end());
        midiActions.clear();
    }
    if(isOscListening){
        vector<vector<string>> oscActions = checkForOsc();
        actionsList.insert(actionsList.end(), oscActions.begin(), oscActions.end());
    }
    if(isAnalogListening){
        vector<vector<string>> analogActions = readAnalogIn();
        actionsList.insert(actionsList.end(), analogActions.begin(), analogActions.end());
        //do nothing for now

    }
    return actionsList;
}


void incur::onKeyPress(int e)// removed this for now KeyListenerEventData& e)
{
    char c = e;
    string s;
    s.push_back(c);
    for( Json::ArrayIndex i = 0; i < result["KEY"].size(); i++){
        if(result["KEY"][i][0].asString() == s){
            vector<string> actionValue = { result["KEY"][i][1].asString(), ""};
            keyActions.push_back(actionValue);
            ofLog() << keyActions.size();
        }
    }
}

void incur::newMidiMessage(ofxMidiMessage& msg) {
    if(msg.status == MIDI_NOTE_ON){
        for( Json::ArrayIndex i = 0; i < result["MIDI"]["NOTE_ON"].size(); i++){
            if(result["MIDI"]["NOTE_ON"][i][0].asString() == ofToString(msg.pitch) ){
                vector<string> actionValue = {result["MIDI"]["NOTE_ON"][i][1].asString(), ""};
                midiActions.push_back(actionValue);
            }
        }
    }
    else if(msg.status == MIDI_CONTROL_CHANGE){
        for( Json::ArrayIndex i = 0; i < result["MIDI"]["CC"].size(); i++){
            if(result["MIDI"]["CC"][i][0].asString() == ofToString(msg.control) ){
                if(msg.value == 0 && midiIgnoreCcOff){}
                else{
                    float normValue = (float)msg.value / (float)127;
                    vector<string> actionValue = {result["MIDI"]["CC"][i][1].asString(), ofToString(normValue)};
                    midiActions.push_back(actionValue);
                }

            }
        }
    }   
}

vector<vector<string>> incur::checkForOsc(){
    vector<vector<string>> oscActions;
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        for( Json::ArrayIndex i = 0; i < result["OSC"].size(); i++){
            if(result["OSC"][i][0].asString() == m.getAddress() ){
                string value = "";
                if(m.getNumArgs() > 0){value = m.getArgAsString(0);}
                float firstParam = m.getArgAsFloat(0);
                vector<string> actionValue = {result["OSC"][i][1].asString(), value};
                oscActions.push_back(actionValue);
            }
        }
    }
    return oscActions;
}

#ifdef TARGET_RASPBERRY_PI
//this is not working yet not sure why ...
void incur::onCharacterReceived(KeyListenerEventData& e){
    ofLog() << "im pressed";
    onKeyPress((int)e.character);
}

#endif

vector<vector<string>> incur::readAnalogIn(){
    vector<vector<string>> analogActions;
#ifdef TARGET_RASPBERRY_PI
    float nowGetTime = ofGetElapsedTimef();
    float timeDiff = nowGetTime - lastGetTime;
    
    if(timeDiff < adcDelay ){return analogActions;}
    else{
        float buttonTimeDiff = nowGetTime - lastButtonTime;
        // first if any gpio pins are low - indicating a button is pressed
       if(buttonTimeDiff > 0.4 ){
            for( Json::ArrayIndex i = 0; i < result["GPIO"].size(); i++){
                int gpioPinNum = ofToInt(result["GPIO"][i][0].asString());
                for( int j = 0; j < gpioList.size(); j++){
                    if(gpioList[j].get_igpionum() == gpioPinNum and gpioList[j].get() == 0){
                        ofLog() << "key is pressed " << result["GPIO"][i][1].asString();
                        lastButtonTime = nowGetTime;
                        vector<string> actionValue = {result["GPIO"][i][1].asString(), ""};
                        analogActions.push_back(actionValue);
                    }
                }
            }
 
        }
        lastGetTime = nowGetTime;
        // next check the a2d on spi0
       
        for( Json::ArrayIndex i = 0; i < result["ANALOG"].size(); i++){
            int a2dIndex = ofToInt(result["ANALOG"][i][0].asString());
            int value = 0;
            if(a2dIndex < 8){
                value = a2d0.getValueAllChannel(chip)[a2dIndex];
            }
            else if(8 <= a2dIndex < 16){
                value = a2d1.getValueAllChannel(chip)[a2dIndex - 8];
            }
            //ofLog() << "value " << value;
            if(value - lastAnalogReading[a2dIndex] < 5 && value - lastAnalogReading[a2dIndex] > -5 ){continue;}
            lastAnalogReading[a2dIndex] = value;
            float normValue = (float)value / (float)1023;
            normValue = roundf(normValue * 100) / 100; 
            vector<string> actionValue = {result["ANALOG"][i][1].asString(), ofToString(normValue)};
            analogActions.push_back(actionValue);
        }
        
    }
#endif
return analogActions;
}


void incur::exit(){
#ifdef TARGET_RASPBERRY_PI
	a2d0.quit();
        a2d1.quit();
#endif
    //midiIn.closePort();
    //midiIn.removeListener(this);

}
