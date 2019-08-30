#pragma once

#include "ofMain.h"
#include "recur.h"



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

	recur recurPlayer;
	ofTexture out_texture;
};
