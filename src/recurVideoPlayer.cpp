#include "recurVideoPlayer.h"

void recurVideoPlayer::setup(string playerType, string nameValue){
    type = playerType;
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    omxSettings.initialVolume = 0.5;
    omxPlayer.setup(omxSettings);
    #endif
    }
    else{
    //ofPlayer.setup();
    
    }
    name = nameValue;
    status = "EMPTY";
    alpha = 255;
    end = 1;
    start = 0;
    speed = 1;
}

void recurVideoPlayer::loadPlayer(string pathValue, float startValue, float endValue, float speedValue){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    ofLog() << "loaded omxplayer";
    omxPlayer.loadMovie(pathValue); 
    #endif
    }
    else{
    ofPlayer.loadAsync(pathValue);
    ofPlayer.setVolume(1.0);    
    }
    
    start = startValue;
    end = endValue;
    speed = speedValue;
}
void recurVideoPlayer::playPlayer(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    omxPlayer.setPaused(false);
    #endif
    }
    else{
    ofPlayer.setPaused(false);
    }
    alpha = 255;    
}
void recurVideoPlayer::pausePlayer(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    omxPlayer.setPaused(true);
    #endif
    }
    else{
    ofPlayer.setPaused(true);
    }
        
}
void recurVideoPlayer::setSpeedTo(float speedValue){
    if(speedValue == 0){ speed = 0.001;}
    else{speed = speedValue;}
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    //omxPlayer.setSpeed(speed);
    #endif
    }
    else{
    ofPlayer.setSpeed(speed);
    }
    
    //ofLog(OF_LOG_NOTICE, "the player speed is " + ofToString(getSpeed()) + "but it should be " + ofToString(speed));   
}
void recurVideoPlayer::close(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    omxPlayer.close();
    #endif
    }
    else{
    ofPlayer.close();
    }
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
            playPlayer();
            //ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(getPosition()));
            
            if(getCurrentFrame() > 2  && getCurrentFrame() < 30){
                //pausePlayer();
                //ofLog(OF_LOG_NOTICE, "the playing frame is " + ofToString(getCurrentFrame()));

                if(start != 0){setPosition(start);}
                //ofLog(OF_LOG_NOTICE, "the position is " + ofToString(getPosition()) + "it should be " + ofToString(start));
                //aPlayer.setSpeed(aSpeed);
                //updateStatus("a", "LOADED");
                status = "LOADED";
                pausePlayer();
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
            //ofLog() << "isAtEndPoint " << isAtEndPoint << " (end) " << end; 
        //    }
        //else{
            //isAtEndPoint = getPosition() < start || getCurrentFrame() < 5;
            //}
        if(isAtEndPoint){
            status = "FINISHED";
            
            pausePlayer();
            return true;
            //updateStatus("a", "FINISHED");
            }
        }
return false;
}

float recurVideoPlayer::getPosition(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    float position = (float)(omxPlayer.getCurrentFrame()) / (float)(omxPlayer.getTotalNumFrames());
    //ofLog() << "position " << ofToString(position) << "media time " << omxPlayer.getMediaTime() / omxPlayer.getDurationInSeconds();
    return position; 
    #else
    return 0.0;
    #endif
    }
    else{
    return ofPlayer.getPosition();
    }
}

int recurVideoPlayer::getCurrentFrame(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    return omxPlayer.getCurrentFrame();
    #else
    return 0;
    #endif
    }
    else{
    return ofPlayer.getCurrentFrame();
    }
}

int recurVideoPlayer::getTotalNumFrames(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    return omxPlayer.getTotalNumFrames();
    #else
    return 0;
    #endif
    }
    else{
    return ofPlayer.getTotalNumFrames();
    }
}


void recurVideoPlayer::setPosition(float pos){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    int frame = (int)(pos * (float)(omxPlayer.getTotalNumFrames()));
    ofLog() << "seeking to frame" << frame;
    omxPlayer.seekToFrame(frame);
    #endif
    }
    else{
    ofPlayer.setPosition(pos);
    }
}

void recurVideoPlayer::draw(int x, int y, int w, int h){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    omxPlayer.draw( x, y, w, h);
    #endif
    }
    else{
    ofPlayer.draw( x, y, w, h);
    }
} 

ofTexture recurVideoPlayer::getTexture(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    return omxPlayer.getTextureReference();
    #else
    return ofPlayer.getTexture();
    #endif
    }
    else{
    return ofPlayer.getTexture();
    }
}

void recurVideoPlayer::update(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    //omxPlayer.update();
    #endif
    }
    else{
    ofPlayer.update();
    }
} 

bool recurVideoPlayer::isLoaded(){
    if(type == "ofxomxplayer"){
    #ifdef TARGET_RASPBERRY_PI
    return true;//omxPlayer.update();
    #else
    return true;
    #endif
    }
    else{
    return ofPlayer.isLoaded();
    }
} 
