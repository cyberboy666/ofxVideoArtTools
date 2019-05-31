#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    recur.setup("video.mp4");
}

//--------------------------------------------------------------
void ofApp::update(){

    recur.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    // out_texture = recur.getSeamlessPlayerTexture();
    // out_texture.draw(0, 0);
    recur.SeamlessPlayerDraw();
    }

//--------------------------------------------------------------
