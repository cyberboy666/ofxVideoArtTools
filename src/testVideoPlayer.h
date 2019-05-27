#pragma once

#include "ofMain.h"
#include "ofVideoPlayer.h"
#include "ofxOsc.h"

class testVideoPlayer : public ofVideoPlayer {

    public:
        void setup();
    ofxOscReceiver receiver;
};
