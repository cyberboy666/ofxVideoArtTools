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

vector<string> getActions(){
    vector<string> actionsList;

    if(isKeyListening){
        // do nothing for now
    }
    if(isMidiListening){
        vector<string> midiActions = checkForMidi();
        actionsList.insert(actionsList.end(), midiActions.begin(), midiActions.end());
    }
    if(isOscListening){
        vector<string> oscActions = checkForOsc();
        actionsList.insert(actionsList.end(), oscActions.begin(), oscActions.end());
    }
    if(isAnalogListening){
        //do nothing for now
    }
    return actionsList;
}

void incur::newMidiMessage(ofxMidiMessage& msg) {
    if(msg.status == MIDI_NOTE_ON){
        for( Json::ArrayIndex i = 0; i < result["MIDI"]["NOTE_ON"].size(); i++){
            
        }
    }
}

void incur::exit(){
    midiIn.closePort();
    midiIn.removeListener(this);
}
