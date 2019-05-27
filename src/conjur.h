#pragma once

#include "ofMain.h"

class conjur{

    public:
        void setup();
        void loadShader(string shaderPath);
        ofFbo apply(vector<ofTexture> textures);

    ofShader shader;
    ofFbo fbo;
    vector<float> shaderParams;
    int paramNum;
    bool isActive;

};
