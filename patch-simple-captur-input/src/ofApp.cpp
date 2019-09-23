#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    consoleListener.setup(this);
    //ofHideCursor();    
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetFullscreen(1);
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());

    //videoInput.setup("vidGrabber");
    videoInput.setup("vidGrabber", ofGetWidth(), ofGetHeight(), 25);
}

//--------------------------------------------------------------
void ofApp::update(){
    videoInput.update();

}
//--------------------------------------------------------------
void ofApp::draw(){
    if(videoInput.isReady()){
        videoInput.draw(0,0);
    }

}


//--------------------------------------------------------------
void ofApp::keyPressed (int key){
    switch(key){
        case 'r':
            videoInput.startRecording();
             break;
        case 'w':
            videoInput.stopRecording();
             break;
        case 's':
            videoInput.setup("vidGrabber", ofGetWidth(), ofGetHeight(), 25);
             break;
        case 'd':
            videoInput.close();
             break;
    }

}

#ifdef TARGET_RASPBERRY_PI
void ofApp::onCharacterReceived(KeyListenerEventData& e){
    ofLog() << "im pressed";
    keyPressed((int)e.character);
}
#endif

