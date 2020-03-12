#include "captur.h"

void captur::setup(string givenType, int w, int h, int fr){
    width = w; //640;
    height = h; //480;
    framerate = fr;//30;

    recorderType = "VideoRecorder";
    recordingPath = "/home/pi/Videos/raw.h264";
    isRecordingOn = false;
    isRecordingFinished = true;

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
    if(grabberType == "vidGrabber" && recorderType == "VideoRecorder"){
        vidRecorder.setVideoCodec("mpeg4");
        vidRecorder.setVideoBitrate("800k");
        ofAddListener(vidRecorder.outputFileCompleteEvent, this, &captur::recordingComplete);
    }
    
}

void captur::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    ofLog() << "recording compete !!!!!!!!!!!!!!!!!!!";
    isRecordingFinished = true;
}

#ifdef TARGET_RASPBERRY_PI
void captur::setOmxCameraSettings(string captureType){

    omxCameraSettings.sensorWidth = width; //fbo.getWidth();
    omxCameraSettings.sensorHeight = height; //fbo.getHeight();
	omxCameraSettings.framerate = framerate; //25;
	omxCameraSettings.enableTexture = true;
    omxCameraSettings.enablePixels = true;

    omxCameraSettings.recordingFilePath = recordingPath;

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
        if(vidGrabber.isFrameNew()){
            if(isRecordingOn && recorderType == "VideoRecorder"){
                bool success = vidRecorder.addFrame(vidGrabber.getPixels());
                if (!success) {
                    ofLogWarning("This frame was not added!");
                }
            }
        }
        
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
        //omxVidGrabber.draw(x,y);
        omxVidGrabber.getTextureReference().draw(x, y, w, h);
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

/*
// this is not being used - trying something but in the end decided not to...
ofTexture captur::getTextureAndResize(int width, int height){
    ofPixels resized_pixels;

    if (grabberType == "vidGrabber"){
        resized_pixels = vidGrabber.getPixels();
    }
    #ifdef TARGET_RASPBERRY_PI
    else{ // if(grabberType == "omxGrabber"){
        resized_pixels = omxVidGrabber.getPixels();
    }
    #endif


    ///seems to run out of resources when trying to resize pixels here even on composite ...
    //resized_pixels.resize(100, 100);//w,h);

    ofTexture resized_texture;
    resized_texture.allocate(width, height, GL_RGB);
    resized_texture.loadData(resized_pixels.getData(),width, height, GL_RGBA );
    return resized_texture;
} 
*/
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
    isRecordingOn = true;
    if (grabberType == "vidGrabber" && recorderType == "VideoRecorder"){
        ofLog() << "starting usb recording !!!!!!!!!!!!!!!!!!!!!!";
        vidRecorder.setup("/home/pi/Videos/raw.mp4", width, height, framerate); // no audio
        vidRecorder.start();
        //nothing yet
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "vidGrabber" && recorderType == "omxRecorder"){
        // do omx stuff here maybe
    }
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.startRecording();
    }
    #endif
}

void captur::stopRecording(){
    isRecordingOn = false;
    if (grabberType == "vidGrabber" && recorderType == "VideoRecorder"){
        ofLog() << "stop usb recording !!!!!!!!!!!!!!!!!!!!!!";
        //nothing yet
        isRecordingFinished = false; // let the callback turn  this on
        vidRecorder.close();
        
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "vidGrabber" && recorderType == "omxRecorder"){
        // do omx stuff here maybe
    }
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.stopRecording();
    }
    #endif
}

bool captur::isRecording(){
    if (grabberType == "vidGrabber"){
        //nothing yet
        return isRecordingOn || !isRecordingFinished;
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        return omxVidGrabber.isRecording();
    }
    #endif
    else{ return false;}
}

void captur::close(){
    if (grabberType == "vidGrabber"){
        vidGrabber.close();
    }
    #ifdef TARGET_RASPBERRY_PI
    else if(grabberType == "omxGrabber"){
        omxVidGrabber.close();
    }
    #endif        
}

