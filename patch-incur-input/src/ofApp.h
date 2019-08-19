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
    void setShaderParam0(string amount);
    void setShaderParam1(string amount);

    void pushButton5();

	void exit(string input);

};
