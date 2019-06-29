#pragma once

#include "ofMain.h"
#include "captur.h"
#ifdef TARGET_RASPBERRY_PI
#include "TerminalListener.h"
#endif

#ifdef TARGET_RASPBERRY_PI
class ofApp : public ofBaseApp, public KeyListener {
#else
class ofApp : public ofBaseApp{
#endif


	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    captur videoInput;

void keyPressed  (int key);
    #ifdef TARGET_RASPBERRY_PI
    TerminalListener consoleListener;
    void onCharacterReceived(KeyListenerEventData& e);
    #endif
};
