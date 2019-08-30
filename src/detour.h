#pragma once

#include "ofMain.h"

class detour {

public:

    void setup();

    int width;
    int height;

    
// detour methods
    ofPixels getFrame(ofPixels in_frame);

    void addFrame(ofPixels in_frame);
    void checkMemory();

    void setStart(float value);
    void setEnd(float value);
    void setPosition(float value);
    void setSpeed(float value);
    void setDelaySize(float value);
    void printState();

    int getEndFrame();
    int subsetMod(int amount);
    float subsetModFloat(float amount);

// detour variables
    vector< vector<ofPixels> > detours;
    vector<ofPixels> detour0;
    vector<ofPixels> detour1;
    vector<ofPixels> detour2;
    vector<ofPixels> detour3;

    ofPixels default_frame;

    float normStart;
    float normEnd;
    float normPosition;
    int write_index;
    float detour_position_part;
    
    bool showInfo;
    int current_detour;
    bool is_playing;
    bool is_recording;
    bool record_loop;
    int detour_position;
    float detour_speed;
    int detour_start;
    int detour_end;
    bool memory_full;
    float mix_position;
    float mix_selection;
    float effect_selection;
    int sample_resolution;
    float sample_speed;

    bool is_delay;
    int delay_size;

};
