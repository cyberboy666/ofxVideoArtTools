#pragma once

#include "recurVideoPlayer.h"

class recur {
    public:
        void setup(string path);
        void update();
        //void drawPlayerIfPlayingOrPaused(recurVideoPlayer player);


        recurVideoPlayer 		aPlayer;
        recurVideoPlayer 		bPlayer;

        void startSeamless(string path);
        void updateSeamless();

        void loadNext(string path);
        void switchNext();
        ofTexture getPlayerTexture();
        void playerDraw();
        bool isLoopSeamless;

        void startSingle(string path);
        void updateSingle();

        void closeAll();
        string nowPlaying;
        string videoPath;

};
