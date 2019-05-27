#include "incur.h"

void incur::setup(string mapPath){
    isKeyListening = true;
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

vector<tuple<string,string>> getActions(){
    vector<tuple<string,string>> actionsList;

    if(isKeyListening){
        actionsList.insert(actionsList.end(), keyActions.begin(), keyActions.end());
        keyActions.clear();
    }
    if(isMidiListening){
        actionsList.insert(actionsList.end(), midiActions.begin(), midiActions.end());
        midiActions.clear();
    }
    if(isOscListening){
        vector<tuple<string, string>> oscActions = checkForOsc();
        actionsList.insert(actionsList.end(), oscActions.begin(), oscActions.end());
    }
    if(isAnalogListening){
        //do nothing for now
    }
    return actionsList;
}

void ofBaseApp::keyPressed(int key){
    onKeyPress(key);
}

void incur::onKeyPress(int e)// removed this for now KeyListenerEventData& e)
{
    for( Json::ArrayIndex i = 0; i < result["KEY"].size(); i++){
        if(result["KEY"][i][0] == ofToString(e.character){
            actionValue = make_tuple(result["KEY"][i][1], "");
            keyActions.push_back(actionValue);
        }
}

void incur::onMidiMessage(ofxMidiMessage& msg) {
    if(msg.status == MIDI_NOTE_ON){
        for( Json::ArrayIndex i = 0; i < result["MIDI"]["NOTE_ON"].size(); i++){
            if(result["MIDI"]["NOTE_ON"][i][0] == ofToString(msg.pitch) ){
                actionValue = make_tuple(result["MIDI"]["NOTE_ON"][i][1], "");
                midiActions.pop(actionValue);
            }
        }
    }
    else if(msg.status == MIDI_CONTROL_CHANGE){
        for( Json::ArrayIndex i = 0; i < result["MIDI"]["CC"].size(); i++){
            if(result["MIDI"]["CC"][i][0] == ofToString(msg.control) ){
                float normValue = (float)msg.value / (float)127;
                actionValue = make_tuple(result["MIDI"]["NOTE_ON"][i][1], ofToString(normValue));
                midiActions.push_back(actionValue);
            }
        }
}

vector<tuple<string,string>> incur::checkForOsc()
{
    vector<tuple<string,string>> oscActions;
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        for( Json::ArrayIndex i = 0; i < result["OSC"].size(); i++){
            if(result["OSC"][i][0] == m.getAddress() ){
                string value = "";
                if(m.getNumArgs() > 0){value = m.getArgAsStr(0);}
                float firstParam = m.getArgAsFloat(0);
                actionValue = make_tuple(result["CC"][i][1], value);
                oscActions.push_back(actionValue);
            }
        }
    }
    return oscActions;
}

void incur::exit(){
    midiIn.closePort();
    midiIn.removeListener(this);
}
