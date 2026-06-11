#include "recur.h"

void recur::setup(string playerType){

    aPlayer.setup(playerType, "a");
    bPlayer.setup(playerType, "b");

    currentSpeed = 1.0f;
    currentSpeedBucket = 2;
    speedPotActive = false;
    initialSpeedPotValue = -1.0f;

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
            bPlayer.setSpeedTo(currentSpeed);
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
            aPlayer.setSpeedTo(currentSpeed);
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
        aPlayer.setSpeedTo(currentSpeed);
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

void recur::setPlay(bool play){
    if(nowPlaying == "a"){
        if(play){aPlayer.playPlayer(); }
        else{aPlayer.pausePlayer(); }
    }
    else if(nowPlaying == "b"){
        if(play){bPlayer.playPlayer(); }
        else{bPlayer.pausePlayer(); }
    }
}

void recur::setSpeed(float normalizedPot) {

    int rawBucket = (int)(normalizedPot * 5);

    int speedBucket = ofClamp(rawBucket, 0, 4);

    float speedMultipliers[5] = {0.25f, 0.5f, 1.0f, 2.0f, 4.0f};

    float speed = speedMultipliers[speedBucket];

    float speedBucketSize = 0.2;
    // Amount of pot change before we actually change the speed, to avoid flapping on boundaries
    float speedChangeMargin = 0.02;

    // User hasn't used the speed pot yet after boot, keep speed at 1x default
    if (speedPotActive == false)  {

        if (initialSpeedPotValue < 0) {
            initialSpeedPotValue = normalizedPot;
            return;
        }
        
        if (initialSpeedPotValue >= 0) {
            float potDiff = abs(normalizedPot - initialSpeedPotValue);

            // User moved the pot enough to activate (5%), now start reading it
            if (potDiff > 0.05) {
                speedPotActive = true;
            }

        } else {
            return;
        }
        
    }

    if (speedBucket == this->currentSpeedBucket) {
        return;
    } else {
        float potDriftLowBoundary = (currentSpeedBucket * speedBucketSize) - speedChangeMargin;

        float potDriftHighBoundary = ((currentSpeedBucket + 1) * speedBucketSize) + speedChangeMargin;

        // Pot change too small (< 2%) to change speed, keep the same speed
        if (normalizedPot > potDriftLowBoundary && normalizedPot < potDriftHighBoundary) {
            return;
        }
        
        this->currentSpeedBucket = speedBucket;
        this->currentSpeed = speed;

        aPlayer.setSpeedTo(speed);
        bPlayer.setSpeedTo(speed);
    }

}

void recur::closeAll(){
    aPlayer.close();
    bPlayer.close();
}



