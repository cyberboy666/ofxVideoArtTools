#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    //userInput new incur();

    userInput.setupThis("actionMap.json");
    userInput.analogListening();
    //incur.newMidiMessage();
}

//--------------------------------------------------------------
void ofApp::update(){
        vector<vector<string>> actionsList = userInput.getActions();
        for( int i = 0; i < actionsList.size(); i++){
            //ofLog() << "action is " << actionsList[i][0] << "value is " << actionsList[i][1];
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
     else if(action == "setShaderParam0"){setShaderParam0(amount);}
     else if(action == "setShaderParam1"){setShaderParam1(amount);}
     else if(action == "pushButton5"){pushButton5();}

 }

void ofApp::pushButton5(){
    ofLog() << "pushButton5 is pressed ! ";
}

void ofApp::setShaderParam0(string amount){
    //ofLog() << "setShaderParam0: " << amount;
}

void ofApp::setShaderParam1(string amount){
    //ofLog() << "setShaderParam1: " << amount;
}

 void ofApp::exit(string input){
    ofExit();
 }
