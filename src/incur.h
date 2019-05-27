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

class incur { // removed this also: public ofxMidiListener{ // removed this for now : public KeyListener,

    public:
        void setup(string mapPath);
        void exit();

        bool midiListening();
        bool oscListening();
        bool analogListening();
        vector<tuple<string, string>> getActions();

    // key listening
    
    bool isKeyListening;
    vector<tuple<string, string>> keyActions;
    void onKeyPress(int e); // removed this for now KeyListenerEventData& e);


    // midi listening 

    bool isMidiListening;
    vector<tuple<string, string>> midiActions;
	void onMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
	std::vector<ofxMidiMessage> midiMessages;
	std::size_t maxMessages = 10; //< max number of messages to keep track of

    // osc listening

    ofxOscReceiver receiver;
    bool isOscListening;
    vector<tuple<string,string>> checkForOsc;
    ofxJSONElement result;

    // analog listening (not implemeted yet)

    bool isAnalogListening;
};