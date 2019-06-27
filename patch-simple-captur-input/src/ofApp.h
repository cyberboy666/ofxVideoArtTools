#pragma once

#include "ofMain.h"
#include "captur.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    captur videoInput;

void keyPressed  (int key);
};
