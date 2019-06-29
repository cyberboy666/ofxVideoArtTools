#include "incur.h"

void incur::setupThis(string mapPath){
    #ifdef TARGET_RASPBERRY_PI
    consoleListener.setup(this);
    #endif
    
    isKeyListening = true;
    keyActions = {};
    isMidiListening = false;
    midiActions = {};
    isOscListening = false;
    isAnalogListening = false;
    bool parsingSuccessful = result.open(mapPath);
}

bool incur::midiListening(){
    midiIn.openPort(1);
    midiIn.addListener(this);
    isMidiListening = midiIn.isOpen();
    return isMidiListening;
}

bool incur::oscListening(){
    receiver.setup(8000);
    isOscListening = true;
    return isOscListening;
}

bool incur::analogListening(){
    isAnalogListening = false;
    return isAnalogListening;
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
                float normValue = (float)msg.value / (float)127;
                vector<string> actionValue = {result["MIDI"]["NOTE_ON"][i][1].asString(), ofToString(normValue)};
                midiActions.push_back(actionValue);
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
                vector<string> actionValue = {result["CC"][i][1].asString(), value};
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


void incur::exit(){
    midiIn.closePort();
    midiIn.removeListener(this);
}
