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

		//---- actions
		void runAction(string action, string amount);
		void togglePlay();
		void toggleRecord();
		void toggleRecordMode();
		void toggleShowState();
		void clearThisDetour();
		void setSpeed(float normValue);
		void setPosition(float normValue);
		void setSpeedIfPlayingElsePosition(float normValue);
		void setMixPosition(float normValue);
		void setStartPosition(float normValue);
		void setEndPosition(float normValue);
		void switchDetour0();
		void switchDetour1();
		void switchDetour2();
		void switchDetour3();

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
	ofFbo mix_fbo;

	vector<float> effectParams;

};
