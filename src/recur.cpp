#include "recur.h"

void recur::setup(){

    aPlayer.setup("ofxomxplayer", "a");
    bPlayer.setup("ofxomxplayer", "b");

    /*isLoopSeamless = true;

    if(isLoopSeamless == true){
        startSeamless(path);
    }
    else{
        startSingle(path);
    }*/
}

void recur::startSeamless(string path){
    closeAll();
    videoPath = path;
    nowPlaying = aPlayer.name;
    aPlayer.loadPlayer(path);
    bPlayer.loadPlayer(path);
    bPlayer.status = "LOADING";
    aPlayer.playPlayer();
    aPlayer.status = "PLAYING";
}

void recur::startSingle(string path){
    closeAll();
    isLoopSeamless = false;
    videoPath = path;
    nowPlaying = aPlayer.name;
    aPlayer.loadPlayer(path);
    
    aPlayer.playPlayer();
    aPlayer.status = "PLAYING";
}


void recur::update(){
    //ofLog() << "playerA: " << aPlayer.status << "playerB: " << bPlayer.status ;
    if (isLoopSeamless){
        updateSeamless();
    }
    else {
        updateSingle();
    }
}

ofTexture recur::getPlayerTexture(){
    if(nowPlaying == "a"){return aPlayer.getTexture();}
    else {return bPlayer.getTexture();} //if(nowPlaying == "b")
}

void recur::playerDraw(){
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
            aPlayer.loadPlayer(videoPath);
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
            bPlayer.loadPlayer(videoPath);
            bPlayer.status = "LOADING";
        }
    }
}


void recur::updateSingle(){
    aPlayer.update();

    bool aIsFinished;
    if(aPlayer.status == "PLAYING"){ aIsFinished = aPlayer.ifPlaying();}
    if(aPlayer.status == "FINISHED"){
        aPlayer.loadPlayer(videoPath);
        aPlayer.status = "LOADING";
    }
    if(aPlayer.status == "LOADING") { aPlayer.ifLoading();}

    if(aPlayer.status == "LOADED"){
        aPlayer.playPlayer();
        aPlayer.status = "PLAYING";
    }


}



void recur::loadNext(string path){
    videoPath = path;
/*    if(nowPlaying == "a"){bPlayer.loadPlayer(path);}
    else if(nowPlaying == "b"){aPlayer.loadPlayer(path);}
*/
}

void recur::switchNext(){
    if(nowPlaying == "a"){
        aPlayer.status = "FINISHED";
    }
    else if(nowPlaying == "b"){
        bPlayer.status = "FINISHED";
    }
/*    if(nowPlaying == "a"){
        if(bPlayer.status == "LOADED"){
            nowPlaying = "b";
            bPlayer.playPlayer();
            bPlayer.status = "PLAYING";
            aPlayer.loadPlayer(videoPath);
            aPlayer.status = "LOADING";
        }
    }
    else if(nowPlaying == "b"){
        if(aPlayer.status == "LOADED"){
            nowPlaying = "a";
            aPlayer.playPlayer();
            aPlayer.status = "PLAYING";
            bPlayer.loadPlayer(videoPath);
            bPlayer.status = "LOADING";
        }
    }
*/
}

bool recur::isLoaded(){
    if(nowPlaying == "a"){
        return aPlayer.isLoaded();
    }
    else if(nowPlaying == "b"){
        return bPlayer.isLoaded();
    }
    return false;
}

void recur::closeAll(){
    aPlayer.close();
    bPlayer.close();
}



