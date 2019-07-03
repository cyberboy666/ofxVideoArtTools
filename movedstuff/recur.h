#pragma once

#include "recurVideoPlayer.h"

class recur {
    public:
        void setup(string video);
        void update();
        //void drawPlayerIfPlayingOrPaused(recurVideoPlayer player);


        recurVideoPlayer 		aPlayer;
        recurVideoPlayer 		bPlayer;

        void startSeamless();
        void updateSeamless();
        ofTexture getSeamlessPlayerTexture();
        void SeamlessPlayerDraw();
        bool isLoopSeamless;
        string nowPlaying;
        string videoPath;

};
