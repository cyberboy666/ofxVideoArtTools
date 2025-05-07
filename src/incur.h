#pragma once

#include "ofMain.h"
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/ioctl.h>
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
        vector<int> getKeyPassthrough();

    float lastButtonTime;
    float lastGetTime;
    // key listening
    int fd = -1;
    struct input_event ev[64];
    int eventSize = sizeof(struct input_event);
    bool shiftHeld = false;
    bool capsLockOn = false;
    bool connectKeyboard(int deviceNumber);
    void readKey();
    #ifdef TARGET_RASPBERRY_PI
    TerminalListener consoleListener;
    void onCharacterReceived(KeyListenerEventData& e);
    // analog inputs
    float adcDelay;
    int adcGrain = 5; 
    MCP a2d;
    MCP_DESC chip = MCP3008;
    vector<int> analogIn;
    // gpio from pushbutton
    GPIO gpio4, gpio5, gpio6, gpio7, gpio9, gpio12, gpio13, gpio18, gpio19, gpio22, gpio23;
    vector<GPIO> gpioList;
    vector<int> lastAnalogReading;
    #endif
    bool isKeyListening;
    bool isKeyPassthrough;
    vector<int> keyPressPassthrough;
    vector<vector<string>> keyActions;
    
    void onKeyPress(int e); // removed this for now KeyListenerEventData& e);


    // midi listening 

    bool isMidiListening;
    bool midiIgnoreCcOff;
    vector<vector<string>> midiActions;
    void newMidiMessage(ofxMidiMessage& eventArgs);
	ofxMidiIn midiIn;
        ofMutex midiMutex; //< MIDI message access mutex 
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

    // key maps:
// Lowercase/default
std::unordered_map<int, int> keyMap = {
    {KEY_A, 'a'}, {KEY_B, 'b'}, {KEY_C, 'c'}, {KEY_D, 'd'}, {KEY_E, 'e'},
    {KEY_F, 'f'}, {KEY_G, 'g'}, {KEY_H, 'h'}, {KEY_I, 'i'}, {KEY_J, 'j'},
    {KEY_K, 'k'}, {KEY_L, 'l'}, {KEY_M, 'm'}, {KEY_N, 'n'}, {KEY_O, 'o'},
    {KEY_P, 'p'}, {KEY_Q, 'q'}, {KEY_R, 'r'}, {KEY_S, 's'}, {KEY_T, 't'},
    {KEY_U, 'u'}, {KEY_V, 'v'}, {KEY_W, 'w'}, {KEY_X, 'x'}, {KEY_Y, 'y'},
    {KEY_Z, 'z'},

    {KEY_1, '1'}, {KEY_2, '2'}, {KEY_3, '3'}, {KEY_4, '4'}, {KEY_5, '5'},
    {KEY_6, '6'}, {KEY_7, '7'}, {KEY_8, '8'}, {KEY_9, '9'}, {KEY_0, '0'},

    {KEY_SPACE, ' '}, {KEY_COMMA, ','}, {KEY_DOT, '.'}, {KEY_SLASH, '/'},
    {KEY_SEMICOLON, ';'}, {KEY_APOSTROPHE, '\''}, {KEY_MINUS, '-'},
    {KEY_EQUAL, '='}, {KEY_LEFTBRACE, '['}, {KEY_RIGHTBRACE, ']'},
    {KEY_BACKSLASH, '\\'}, {KEY_GRAVE, '`'},

    {KEY_ENTER, 10}, {KEY_BACKSPACE, 127}, {KEY_ESC, 27}, {KEY_F1, 80}
};

// Shifted values
std::unordered_map<int, int> shiftMap = {
    {KEY_A, 'A'}, {KEY_B, 'B'}, {KEY_C, 'C'}, {KEY_D, 'D'}, {KEY_E, 'E'},
    {KEY_F, 'F'}, {KEY_G, 'G'}, {KEY_H, 'H'}, {KEY_I, 'I'}, {KEY_J, 'J'},
    {KEY_K, 'K'}, {KEY_L, 'L'}, {KEY_M, 'M'}, {KEY_N, 'N'}, {KEY_O, 'O'},
    {KEY_P, 'P'}, {KEY_Q, 'Q'}, {KEY_R, 'R'}, {KEY_S, 'S'}, {KEY_T, 'T'},
    {KEY_U, 'U'}, {KEY_V, 'V'}, {KEY_W, 'W'}, {KEY_X, 'X'}, {KEY_Y, 'Y'},
    {KEY_Z, 'Z'},

    {KEY_1, '!'}, {KEY_2, '@'}, {KEY_3, '#'}, {KEY_4, '$'}, {KEY_5, '%'},
    {KEY_6, '^'}, {KEY_7, '&'}, {KEY_8, '*'}, {KEY_9, '('}, {KEY_0, ')'},

    {KEY_MINUS, '_'}, {KEY_EQUAL, '+'}, {KEY_LEFTBRACE, '{'},
    {KEY_RIGHTBRACE, '}'}, {KEY_BACKSLASH, '|'}, {KEY_SEMICOLON, ':'},
    {KEY_APOSTROPHE, '\"'}, {KEY_GRAVE, '~'}, {KEY_COMMA, '<'},
    {KEY_DOT, '>'}, {KEY_SLASH, '?'}
};

};
