#pragma once

#include "ofMain.h"
#include "incur.h"
#include "captur.h"
#include "conjur.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    ofFbo fbo;
    incur incur;
	captur captur;
	conjur mixConjur;
	conjur effectConjur;

	detour detour;
};
