#include "conjur.h"

void conjur::setup(){
    //init the params and setup fbo (not sure if needed)
    isActive = true;
    shaderParams = {0, 0, 0, 0};
    paramNum = 0;

    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();
}

void conjur::loadShader(string shaderPath){
    shader.load(shaderPath);
}

void conjur::loadShaderFiles(string shaderPathFrag, string shaderPathVert){
    shader.load(shaderPathFrag, shaderPathVert);
}

ofFbo conjur::apply(vector<ofTexture> textures){

    if(isActive){
        fbo.begin();
            shader.begin();
                shader.setUniform1f("u_time", ofGetElapsedTimef());
                shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
                for( int i = 0; i <  shaderParams.size(); i = i + 1){
                    shader.setUniform1f("u_x" + ofToString(i), shaderParams[i]);
                    }
                for( int i = 0; i <  textures.size(); i = i + 1){
                    shader.setUniformTexture("u_tex" + ofToString(i), textures[i], i);
                    }
                textures[0].draw(0, 0, ofGetWidth(), ofGetHeight());
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
