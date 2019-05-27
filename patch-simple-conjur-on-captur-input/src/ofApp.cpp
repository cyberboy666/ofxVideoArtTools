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

    captur.setup("vidGrabber");
    conjur.setup();
    conjur.loadShader(shaderPath);
}

//--------------------------------------------------------------
void ofApp::update(){
    captur.update();
    vector<ofTexture> input = { captur.getTexture()};
    fbo = conjur.apply(input);
    }

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0,0);
    }

//--------------------------------------------------------------
