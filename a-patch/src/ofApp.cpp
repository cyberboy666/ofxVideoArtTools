#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
        
    ofSetFullscreen(1);
    fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());

    recurPlayer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    }

//--------------------------------------------------------------
void ofApp::draw(){
    }

//--------------------------------------------------------------
