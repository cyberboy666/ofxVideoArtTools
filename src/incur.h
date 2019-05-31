#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOSC.h"
#include "ofxJSON.h"
#include "ofBaseApp.h"
#ifdef TARGET_RASPBERRY_PI
#include "ofxGPIO.h"
#include "TerminalListener.h"
#endif

class incur : public ofxMidiListener { // removed this for now : public KeyListener,

    public:
        //incur();
        void setupThis(string mapPath);
        void exit();

        bool midiListening();
        bool oscListening();
        bool analogListening();
        vector<vector<string>> getActions();

    // key listening
    
    bool isKeyListening;
    vector<vector<string>> keyActions;
    
    void onKeyPress(int e); // removed this for now KeyListenerEventData& e);


    // midi listening 

    bool isMidiListening;
    vector<vector<string>> midiActions;
    void newMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of

    // osc listening

    ofxOscReceiver receiver;
    bool isOscListening;
    vector<vector<string>> checkForOsc();
    ofxJSONElement result;

    // analog listening (not implemeted yet)

    bool isAnalogListening;
};