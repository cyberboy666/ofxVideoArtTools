#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

    userInput.setup("actionMap.json");
    //incur.newMidiMessage();
}

//--------------------------------------------------------------
void ofApp::update(){
        vector<tuple<string, string>> actionsList = userInput.getActions();
        for( int i = 0; i < actionsList.size(); i++){
            ofLog() << "action is " << get<0>(actionsList[i]) << "value is " << get<1>(actionsList[i]);
        }
    }

//--------------------------------------------------------------
void ofApp::draw(){

    }

//--------------------------------------------------------------
