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

        void startRecording();
        void stopRecording();
        bool isRecording();

        ofxVideoRecorder    vidRecorder;
        bool isRecordingOn;
        bool isRecordingFinished;
        string recordingPath;

        string grabberType;
        string recorderType;
        int width, height;
        float framerate;

        ofVideoGrabber vidGrabber;
        void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args);
        #ifdef TARGET_RASPBERRY_PI
        ofxOMXVideoGrabber omxVidGrabber;
        ofxOMXCameraSettings omxCameraSettings;
        void setOmxCameraSettings(string captureType);
        #endif
};
