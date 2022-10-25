#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"
#include "ofxJSON.h"
#include "ofBaseApp.h"
#ifdef TARGET_RASPBERRY_PI
#include "TerminalListener.h"
#include "ofxGPIO.h"
#endif

#ifdef TARGET_RASPBERRY_PI
class incur : public ofxMidiListener, public KeyListener {
#else
class incur : public ofxMidiListener {
#endif
    public:
        //incur();
        void setupThis(string mapPath);
        void exit();

        bool midiListening(bool ignoreCcOff = false);
        bool oscListening();
        bool analogListening();
        vector<vector<string>> getActions();

    float lastButtonTime;
    float lastGetTime;
    // key listening
    #ifdef TARGET_RASPBERRY_PI
    TerminalListener consoleListener;
    void onCharacterReceived(KeyListenerEventData& e);
    // analog inputs
    float adcDelay; 
    MCP a2d0;
    MCP a2d1;
    MCP_DESC chip = MCP3008;
    vector<int> analogIn;
    // gpio from pushbutton
    GPIO gpio4, gpio5, gpio6, gpio7, gpio9, gpio12, gpio13, gpio18, gpio19, gpio22, gpio23;
    vector<GPIO> gpioList;
    vector<int> lastAnalogReading;
    #endif
    bool isKeyListening;
    vector<vector<string>> keyActions;
    
    void onKeyPress(int e); // removed this for now KeyListenerEventData& e);


    // midi listening 

    bool isMidiListening;
    bool midiIgnoreCcOff;
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
    vector<vector<string>> analogActions;
    vector<vector<string>> readAnalogIn();
      
};
