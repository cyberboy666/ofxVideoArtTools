#include "recurVideoPlayer.h"

void recurVideoPlayer::setup(string nameValue){
    name = nameValue;
    status = "EMPTY";
    alpha = 255;
    end = 1;
    start = 0;
    speed = 1;
}

void recurVideoPlayer::loadPlayer(string pathValue, float startValue, float endValue, float speedValue){
    loadAsync(pathValue); 
    start = startValue;
    end = endValue;
    speed = speedValue;
}
void recurVideoPlayer::playPlayer(){
        setPaused(false);
        alpha = 255;    
}
void recurVideoPlayer::pausePlayer(){
        setPaused(true);
}
void recurVideoPlayer::setSpeedTo(float speedValue){
        if(speedValue == 0){ speed = 0.001;}
        else{speed = speedValue;}
        setSpeed(speed);
        ofLog(OF_LOG_NOTICE, "the player speed is " + ofToString(getSpeed()) + "but it should be " + ofToString(speed));   
}
void recurVideoPlayer::quitPlayer(){
            //stop();
            //close();
}
bool recurVideoPlayer::ifLoading(){
    if(isLoaded()){
        if( status == "LOADING"){

    //get begin point based on direction
            //float beginPoint = start;
            //if(speed < 0 ){
            //    beginPoint = end;
               // }
            //firstFrame();
            setPaused(false);
            ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(getPosition()));
            
            if(getPosition() > 0  && getPosition() < 100){
                setPaused(true);
                //ofLog(OF_LOG_NOTICE, "the playing frame is " + ofToString(getCurrentFrame()));

                if(start != 0){setPosition(start);}
                ofLog(OF_LOG_NOTICE, "the position is " + ofToString(getPosition()) + "it should be " + ofToString(start));
                //aPlayer.setSpeed(aSpeed);
                //updateStatus("a", "LOADED");
                status = "LOADED";
                return true;
                }
            }
        }
return false;
}
bool recurVideoPlayer::ifPlaying(){
    if(status == "PLAYING"){
        //get end point based on direction
        //if(getSpeed() != speed ){setSpeed(speed);}
          
        bool isAtEndPoint;
        //if(speed >= 0){
            isAtEndPoint = getPosition() > end || getCurrentFrame() > getTotalNumFrames() - 5;
        //    }
        //else{
            //isAtEndPoint = getPosition() < start || getCurrentFrame() < 5;
            //}
        if(isAtEndPoint){
            status = "FINISHED";
            setPaused(true);
            return true;
            //updateStatus("a", "FINISHED");
            }
        }
return false;
}


