#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    //userInput new incur();

    userInput.setupThis("actionMap.json");
    //incur.newMidiMessage();
}

//--------------------------------------------------------------
void ofApp::update(){
        vector<vector<string>> actionsList = userInput.getActions();
        for( int i = 0; i < actionsList.size(); i++){
            ofLog() << "action is " << actionsList[i][0] << "value is " << actionsList[i][1];
            runAction(actionsList[i][0], actionsList[i][1]);
        }
    }

//--------------------------------------------------------------
void ofApp::draw(){

    }

//--------------------------------------------------------------
// a work around for now (would rather be hooking keypress from within incur buit seemd harder)
void ofApp::keyPressed  (int key){
    userInput.onKeyPress(key);
}
// also here was hoping to have a map of pointers to the function , but also seemd more tricky than it needs to be
 void ofApp::runAction(string action, string amount){
     if(action == "exit"){ exit(amount);}
     else if(action == "somethingElse"){}
 }

 void ofApp::exit(string input){
    ofExit();
 }