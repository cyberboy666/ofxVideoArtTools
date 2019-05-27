#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "recur.h"
#include "captur.h"

#include "testVideoPlayer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    recur recurPlayer;


};
