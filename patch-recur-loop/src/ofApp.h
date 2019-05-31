#pragma once

#include "ofMain.h"
#include "recur.h"



class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

	recur recur;
	ofTexture out_texture;
};
