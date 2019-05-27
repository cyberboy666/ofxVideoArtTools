#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "TerminalListener.h"
#include "ofxOSC.h"
#include "ofxJSON.h"
#ifdef TARGET_RASPBERRY_PI
#include "ofxGPIO.h"
#endif

class incur : public KeyListener, public ofxMidiListener{

    public:
        void setup(string mapPath);
        void exit();

        bool midiListening();
        bool oscListening();
        bool analogListening();
        vector<string> getActions();

    // key listening
    
    bool isKeyListening;
    void onCharacterReceived(KeyListenerEventData& e);


    // midi listening 

    bool isMidiListening;
    vector<string> midiActions();
	void newMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of

    // osc listening

    ofxOscReceiver receiver;
    bool isOscListening;
    ofxJSONElement result;

    // analog listening (not implemeted yet)

    bool isAnalogListening;
};