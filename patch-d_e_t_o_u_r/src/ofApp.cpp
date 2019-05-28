#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

    captur.setup("vidGrabber");
    incur.setup("actionMap.json");
    detour.setup();

    string shaderPath;
    #ifdef TARGET_OPENGLES
	shaderPath = "shadersES2/";
    #else
	shaderPath = "shadersGL3/mixShader";
    #endif

    mixConjur.setup();
    mixConjur.loadShader(shaderPath + "mixShader");
    effectConjur.setup();
    effectConjur.loadShader(shaderPath + "effectShader");

}

//--------------------------------------------------------------
void ofApp::update(){

    in_frame.setFromPixels(captur.getPixels().getData(), captur.width, captur.height, 3);
    in_frame.resize(ofGetWidth, ofGetHeight);
    detour_frame = detour.getFrame();

    in_texture.loadData(in_frame.getData(), ww, hh, GL_RGBA);
    detour_texture.loadData(detour_frame.getData(), ww, hh, GL_RGBA);

    <ofTexture> mixInput = {in_texture, detour_texture};
    mix_fbo = mixConjur.apply(mixInput);
    
    ofTexture mix_texture = mix_fbo.getTexture();
    <ofTexture> effectInput = {mix_texture};
    out_fbo = effectConjur.apply(effectInput);

    if(is_recording){
        out_fbo.readToPixels(out_frame);
        addFrameToDetour(out_frame); }  
    }   

        vector<tuple<string, string>> actionsList = incur.getActions();
        for( int i = 0; i < actionsList.size(); i++){
            ofLog() << "action is " << get<0>(actionsList[i]) << "value is " << get<1>(actionsList[i]);
        }
    }

//--------------------------------------------------------------
void ofApp::draw(){
        out_fbo.draw(0, 0);
    }

//--------------------------------------------------------------
