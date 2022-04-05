#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
    ofHideCursor();    
        
    //ofSetFullscreen(1);
    //fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();

    recurPlayer.setup();
    recurPlayer.startSingle("/home/timcaldwell/Videos/cyberboy666/lan_party_01.mp4");
    // ofPlayer.setPixelFormat(OF_PIXELS_RGBA);
    // ofPlayer.load("/home/timcaldwell/Videos/cyberboy666/lan_party_01.mp4");
    // ofLog() << "width is " << ofPlayer.getWidth();
    // ofPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    recurPlayer.update();
    // ofPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    recurPlayer.playerDraw();
    // ofPlayer.draw(0,0);
    }

//--------------------------------------------------------------
