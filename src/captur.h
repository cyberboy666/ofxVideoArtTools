#pragma once

#include "ofMain.h"
#ifdef TARGET_RASPBERRY_PI
#include "ofxOMXVideoGrabber.h"
#endif
#include "ofxVideoRecorder.h"

class captur{

    public:
        void setup(string type);
        void update();
        void draw(int x =0, int y=0);
        void draw(int x, int y,int w,int h);
        ofPixels getPixels();
        ofTexture getTexture();
        bool isReady();
        void close();
        bool isFrameNew();
        // for now i will not implement recording here since in some cases recording may be seperate from capturing
        void startRecording();
        void stopRecording();
        bool isRecording();

        ofxVideoRecorder    vidRecorder;
        bool isRecordingOn;
        string recordingPath;

        string grabberType;
        string recorderType;
        int width, height;
        float framerate;

        ofVideoGrabber vidGrabber;
        #ifdef TARGET_RASPBERRY_PI
        ofxOMXVideoGrabber omxVidGrabber;
        ofxOMXCameraSettings omxCameraSettings;
        void setOmxCameraSettings(string captureType);
        #endif
};
