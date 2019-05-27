#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
        
    ofSetFullscreen(1);
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());

    videoInput.setup("vidGrabber");
}

//--------------------------------------------------------------
void ofApp::update(){
    videoInput.update();
    }

//--------------------------------------------------------------
void ofApp::draw(){
    videoInput.draw();
    }

//--------------------------------------------------------------
