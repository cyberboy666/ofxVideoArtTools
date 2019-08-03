#pragma once

#include "ofMain.h"

class conjur{

    public:
        void setup();
        void loadShader(string shaderPath);
        void loadShaderFiles(string shaderPathFrag, string shaderPathVert);
        void setDefaultParams(vector<ofTexture> textures);
        void setAltParams(vector<ofTexture> textures);
        ofFbo apply(vector<ofTexture> textures);

    ofShader shader;
    ofFbo fbo;
    vector<float> shaderParams;
    int paramNum;
    bool isActive;

};
