#pragma once

#include "ofMain.h"

class conjur{

    public:
        void setup();
        void loadShader(string shaderPath);
        void loadShaderFiles(string shaderPathFrag, string shaderPathVert);
        void setSpeed(float value);
        void setPlay(bool play);
        float getTime();
        void setDefaultParams(vector<ofTexture> textures, float time);
        void setAltParams(vector<ofTexture> textures, float time);
        ofFbo apply(vector<ofTexture> textures);

    ofShader shader;
    ofFbo fbo;
    vector<float> shaderParams;
    float speed;
    float time;
    float lastElapsedTime;
    int paramNum;
    bool isActive;

};
