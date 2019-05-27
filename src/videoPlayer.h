#pragma once

#include "ofMain.h"
#include "ofVideoPlayer.h"

class videoPlayer : public ofVideoPlayer {

    public:
        void setup(string nameValue);
        void loadPlayer(string path, float start, float end, float speed);
        void playPlayer();
        void pausePlayer();
        void setSpeedTo(float speedValue);
        void quitPlayer();
        bool ifLoading();
        bool ifPlaying();

        int alpha;
        float start;
        float end;
        float speed;
        string status;
        string name;
};
