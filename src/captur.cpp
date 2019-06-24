#include "captur.h"

void captur::setup(string givenType){
    // hardcode the captur resolution and framerate for now
    width = 640;
    height = 480;
    framerate = 30;

    // convert the capture type to a grabber type
    if(givenType == "piCamera" || givenType == "piCaptureSd1"){ 
        grabberType = "omxGrabber"; 
    }
    else{
        grabberType = "vidGrabber";
    }

    if(grabberType == "vidGrabber"){
        vidGrabber.setDeviceID(0);
        vidGrabber.setDesiredFrameRate(framerate);
        vidGrabber.initGrabber(width, height);
        // vidGrabber.setPixelFormat(GL_RGBA);
    }
    else if(grabberType == "omxGrabber"){
        #ifdef TARGET_RASPBERRY_PI
        setOmxCameraSettings(givenType);
        omxVidGrabber.setup(omxCameraSettings);
        #endif
    }
}

#ifdef TARGET_RASPBERRY_PI
void captur::setOmxCameraSettings(string captureType){

    omxCameraSettings.sensorWidth = width; //fbo.getWidth();
    omxCameraSettings.sensorHeight = height; //fbo.getHeight();
	omxCameraSettings.framerate = framerate; //25;
	omxCameraSettings.enableTexture = true;

    omxCameraSettings.recordingFilePath = "/home/pi/Videos/raw.h264";

    if(captureType == "piCaptureSd1"){
        omxCameraSettings.sensorMode = 7;
        omxCameraSettings.whiteBalance ="Off";
        omxCameraSettings.exposurePreset ="Off";
        omxCameraSettings.whiteBalanceGainR = 1.0;
        omxCameraSettings.whiteBalanceGainB = 1.0;
    }

}
#endif

void captur::update(){
    if (grabberType == "vidGrabber"){
        vidGrabber.update();
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        //omxVidGrabber.update();
    }
    #endif
}

void captur::draw(int x, int y){    
    if (grabberType == "vidGrabber"){
        vidGrabber.draw(x,y);
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.draw(x,y);
    }
    #endif
}

void captur::draw(int x, int y, int w, int h){    
    if (grabberType == "vidGrabber"){
        vidGrabber.draw(x,y, w,h);
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.draw(x,y);
    }
    #endif
}

ofPixels captur::getPixels(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.getPixels();
    }
    #ifdef TARGET_RASPBERRY_PI
    else{ // if(grabberType == "omxGrabber"){
        return omxVidGrabber.getPixels();
    }
    #endif
} 

ofTexture captur::getTexture(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.getTexture();
    }
    #ifdef TARGET_RASPBERRY_PI
    else{ // if(grabberType == "omxGrabber"){
        return omxVidGrabber.getTextureReference();
    }
    #endif
} 

bool captur::isReady(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.isInitialized();
    }
    #ifdef TARGET_RASPBERRY_PI
    else{ // if(grabberType == "omxGrabber"){
        return omxVidGrabber.isReady();
    }
    #endif    
}

bool captur::isFrameNew(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.isFrameNew();
    }
    #ifdef TARGET_RASPBERRY_PI
    else{ // if(grabberType == "omxGrabber"){
        return omxVidGrabber.isFrameNew();
    }
    #endif    
}

void captur::startRecording(){
    if (grabberType == "vidGrabber"){
        //nothing yet
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.startRecording();
    }
    #endif
}

void captur::stopRecording(){
    if (grabberType == "vidGrabber"){
        //nothing yet
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.stopRecording();
    }
    #endif
}

void captur::close(){
    if (grabberType == "vidGrabber"){
        return vidGrabber.close();
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        return omxVidGrabber.close();
    }
    #endif        
}

