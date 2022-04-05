#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
        
    //ofSetFullscreen(1);
    //fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
    fbo.allocate(ofGetWidth(), ofGetHeight());
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();

    string shaderPath;
    #ifdef TARGET_OPENGLES
	shaderPath = "shadersES2/mixShader";
    #else
	shaderPath = "shadersGL3/mixShader";
    #endif

    capture.setup("vidGrabber", ofGetWidth(), ofGetHeight(), 25);
    conjure.setup();
    conjure.loadShader(shaderPath);
}

//--------------------------------------------------------------
void ofApp::update(){
    capture.update();
    vector<ofTexture> input = { capture.getTexture()};
    fbo = conjure.apply(input);
    }

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);
    }

//--------------------------------------------------------------
