#pragma once

#include "ofMain.h"
#include "incur.h"
#include "captur.h"
#include "conjur.h"
#include "detour.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

    incur incur;
	captur captur;
	conjur mixConjur;
	conjur effectConjur;

	detour detour;

	ofPixels in_frame;
	ofPixels detour_frame;
	ofPixels out_frame;
	ofTexture in_texture;
	ofTexture detour_texture;
	ofFbo out_fbo;
};
