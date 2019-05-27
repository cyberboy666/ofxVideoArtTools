#pragma once

#include "ofMain.h"
#include "incur.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    incur userInput;


};
