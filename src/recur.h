#pragma once

#include "videoPlayer.h"

class recur {
    public:
        void setup(string video);
        void update();
        void drawPlayerIfPlayingOrPaused(videoPlayer player);


        videoPlayer 		aPlayer;
        videoPlayer 		bPlayer;

        void startSeamless();
        void updateSeamless();
        ofTexture getSeamlessPlayerTexture();
        void SeamlessPlayerDraw();
        bool isLoopSeamless;
        string nowPlaying;
        string videoPath;

};