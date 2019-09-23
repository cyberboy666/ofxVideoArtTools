#include "conjur.h"

void conjur::setup(){
    //init the params and setup fbo (not sure if needed)
    isActive = true;
    shaderParams = {0, 0, 0, 0};
    paramNum = 0;
    speed = 1;
    time = 0;
    lastElapsedTime = 0;
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();
}

void conjur::loadShader(string shaderPath){
    //this method isnt used ??
    shader.load(shaderPath);
}

void conjur::loadShaderFiles(string shaderPathFrag, string shaderPathVert){
    shader.load(shaderPathFrag, shaderPathVert);
}

ofFbo conjur::apply(vector<ofTexture> textures){
    float time = getTime();
    if(isActive){
        fbo.begin();
            shader.begin();
                setDefaultParams(textures, time);
                setAltParams(textures, time);
                if(textures.size() > 0 ){
                    textures[0].draw(0, 0, ofGetWidth(), ofGetHeight());
                }
                else{
                    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
                }
            shader.end();
        fbo.end();
    }
    else{
        fbo.begin();
            textures[0].draw(0, 0, ofGetWidth(), ofGetHeight());
        fbo.end();
    }
    return fbo;
}

void conjur::setDefaultParams(vector<ofTexture> textures, float time){
    shader.setUniform1f("u_time", time);
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    for( int i = 0; i < shaderParams.size(); i = i + 1){
        shader.setUniform1f("u_x" + ofToString(i), shaderParams[i]);        
        }
    for( int i = 0; i <  textures.size(); i = i + 1){
        shader.setUniformTexture("u_tex" + ofToString(i), textures[i], i);
    }
}

void conjur::setAltParams(vector<ofTexture> textures, float time){
    shader.setUniform1f("ftime", (time) - (long)time);
    shader.setUniform1i("itime", ceil(time));
    shader.setUniform2f("tres", ofGetWidth(), ofGetHeight());
    shader.setUniform4f("fparams", shaderParams[0], shaderParams[1], shaderParams[2], shaderParams[3] );
    shader.setUniform4i("iparams",0,0,0,0);
    
    for( int i = 0; i <  textures.size(); i = i + 1){
        if(i == 0){
            shader.setUniformTexture("tex", textures[i], i);
        }
        else{
            shader.setUniformTexture("tex" + ofToString(i + 1), textures[i], i);
        }
    }
}

void conjur::setSpeed(float value){
    speed = -2.0 + 4.0*value;    
}

float conjur::getTime(){
    float currentElapsedTime = ofGetElapsedTimef();
    float diff = lastElapsedTime - currentElapsedTime;
    time = time + (speed*diff);
    lastElapsedTime = currentElapsedTime;
    return time;    
}

