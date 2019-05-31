#include "recur.h"

void recur::setup(string video){
    videoPath = video;
    aPlayer.setup("a");
    bPlayer.setup("b");

    isLoopSeamless = true;
    startSeamless();
}

void recur::startSeamless(){
    nowPlaying = aPlayer.name;
    aPlayer.load(videoPath);
    bPlayer.load(videoPath);
    bPlayer.status = "LOADING";
    aPlayer.playPlayer();
    aPlayer.status = "PLAYING";
}

void recur::update(){
    ofLog() << "playerA: " << aPlayer.status << "playerB: " << bPlayer.status ;
    if (isLoopSeamless){
        updateSeamless();
    }
}

ofTexture recur::getSeamlessPlayerTexture(){
    if(nowPlaying == "a"){return aPlayer.getTexture();}
    else if(nowPlaying == "b"){return bPlayer.getTexture();}
}

void recur::SeamlessPlayerDraw(){
    if(nowPlaying == "a"){aPlayer.draw(0,0, ofGetWidth(), ofGetHeight());}
    else if(nowPlaying == "b"){return bPlayer.draw(0,0, ofGetWidth(), ofGetHeight());}
}

void recur::updateSeamless(){
    aPlayer.update();
    bPlayer.update();

    if(nowPlaying == "a"){
        bool aIsFinished;
        if(aPlayer.status == "PLAYING"){ aIsFinished = aPlayer.ifPlaying();}
        if(aIsFinished){aPlayer.pausePlayer();}
        if(bPlayer.status == "LOADING") { bPlayer.ifLoading();}

        if(aPlayer.status == "FINISHED" && bPlayer.status == "LOADED"){
            nowPlaying = "b";
            bPlayer.playPlayer();
            bPlayer.status = "PLAYING";
            aPlayer.loadAsync(videoPath);
            aPlayer.status = "LOADING";
        }
    }
    else if(nowPlaying == "b"){
        bool bIsFinished;
        if(bPlayer.status == "PLAYING"){ bIsFinished = bPlayer.ifPlaying();}
        if(bIsFinished){bPlayer.pausePlayer();}
        if(aPlayer.status == "LOADING") { aPlayer.ifLoading();}

        if(bPlayer.status == "FINISHED" && aPlayer.status == "LOADED"){
            nowPlaying = "a";
            aPlayer.playPlayer();
            aPlayer.status = "PLAYING";
            bPlayer.loadAsync(videoPath);
            bPlayer.status = "LOADING";
        }
    }
}
