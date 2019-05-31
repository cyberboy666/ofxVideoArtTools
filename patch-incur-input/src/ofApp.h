#pragma once

#include "ofMain.h"
#include "incur.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

	void keyPressed(int key);
    ofFbo fbo;
    incur userInput;

	void runAction(string action, string amount);

	void exit(string input);

};
