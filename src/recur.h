#pragma once

#include "videoPlayer.h"

class recur {
    public:
        void setup();
        void drawPlayerIfPlayingOrPaused(videoPlayer player);

        videoPlayer 		aPlayer;
        videoPlayer 		bPlayer;

};