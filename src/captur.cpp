#include "captur.h"

void captur::setup(string givenType){
    // hardcode the captur resolution and framerate for now
    width = 640;
    height = 480;
    framerate = 30;

    // convert the capture type to a grabber type
    if(givenType == "piCamera" || givenType == "piCapture"){ 
        grabberType = "omxGrabber"; 
    }
    else{
        grabberType = "vidGrabber";
    }

    if(givenType == "vidGrabber"){
        vidGrabber.setDeviceID(0);
        vidGrabber.setDesiredFrameRate(framerate);
        vidGrabber.initGrabber(width, height);
    }

}

void captur::update(){
    if (grabberType == "vidGrabber"){
        vidGrabber.update();
    }
}

void captur::draw(int x, int y){
    if (grabberType == "vidGrabber"){
        vidGrabber.draw(x,y);
    }
}

ofPixels captur::getPixels(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.getPixels();
    }
} 

ofTexture captur::getTexture(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.getTexture();
    }
} 

bool captur::isReady(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.isInitialized();
    }    
}

void captur::close(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.close();
    }    
}

