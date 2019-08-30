#pragma once

#include "ofMain.h"
#include "ofVideoPlayer.h"
#ifdef TARGET_RASPBERRY_PI
#include "ofxOMXPlayer.h"
#endif

class recurVideoPlayer{

    public:
        ofVideoPlayer ofPlayer;
        #ifdef TARGET_RASPBERRY_PI
        ofxOMXPlayerSettings omxSettings;
        ofxOMXPlayer omxPlayer;
        #endif  

        void setup(string playerType, string nameValue);
        void loadPlayer(string path, float start=0, float end=1, float speed=1);
        void playPlayer();
        void pausePlayer();
        void setSpeedTo(float speedValue);
        void close();
        bool ifLoading();
        bool ifPlaying();

        float getPosition();
        void setPosition(float pos);
        int getCurrentFrame();
        int getTotalNumFrames();
        void draw(int x, int y, int w, int h);
        ofTexture getTexture();
        void update();
        bool isLoaded();

        
        string type;
        int alpha;
        float start;
        float end;
        float speed;
        string status;
        string name;
};
