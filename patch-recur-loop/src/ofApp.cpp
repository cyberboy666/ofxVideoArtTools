#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    recurPlayer.setup("/home/pi/Videos/motorway01.mp4");
}

//--------------------------------------------------------------
void ofApp::update(){

    recurPlayer.update();
}
//--------------------------------------------------------------
void ofApp::draw(){
    // out_texture = recur.getSeamlessPlayerTexture();
    // out_texture.draw(0, 0);
    recurPlayer.playerDraw();
    }

//--------------------------------------------------------------
