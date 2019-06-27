#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    //ofHideCursor();    
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    //ofSetFullscreen(1);
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());

    videoInput.setup("vidGrabber");
    //videoInput.setup("piCamera");
}

//--------------------------------------------------------------
void ofApp::update(){
    videoInput.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    videoInput.draw(0,0);

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
    }

}