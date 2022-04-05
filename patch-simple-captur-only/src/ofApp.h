#pragma once

#include "ofMain.h"
#include "captur.h"
#include "conjur.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    captur capture;
	conjur conjure;


};
