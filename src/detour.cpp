#include "detour.h"

//--------------------------------------------------------------
void detour::setup(){

	ofEnableAlphaBlending();

    detours = {detour0, detour1, detour2, detour3};
    current_detour = 0;
    is_playing = false;
    is_recording = false;
    record_loop = false;
    detour_position = 0;
    detour_speed = 1;
    detour_start = 0;
    detour_end = 0;
    memory_full = false;
    sample_resolution = 0;
    sample_speed = 1;
    mix_position = 0.0;
    mix_selection = 0.0;

    showInfo = false;

    is_delay = false;
    delay_size = 10;

    normPosition = 0;
    normStart = 0;
    normEnd = 0;

    write_index = 0;

    ofImage img;
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
    img.setColor(ofColor::red);
    img.update();
    default_frame = img.getPixels();

}

ofPixels detour::getFrame(){

    if(detours[current_detour].size() == 0){ return default_frame; }


    ofPixels this_frame = detours[current_detour][detour_position];

    if(is_playing){
        detour_position_part = subsetModFloat(detour_position_part + detour_speed);
        detour_position = (int)floor(detour_position_part);
    }
    // if(is_delay){ // need to refactor delay lolgic later
    //     int current_size = detours[current_detour].size();
    //     detour_position = current_size - 1;
    //     this_frame = detours[current_detour][detour_position];
    //     if(current_size > delay_size){
    //         detours[current_detour].erase(detours[current_detour].begin()+delay_size,detours[current_detour].begin()+current_size);
    //     }
    //     detours[current_detour].insert(detours[current_detour].begin(),in_frame);
    // }

    return this_frame;
}

void detour::addFrame(ofPixels in_frame){
    if(record_loop | memory_full ){
        detours[current_detour][write_index] = in_frame;
        write_index = subsetMod(write_index + 1);
    }
    else{
        detours[current_detour].push_back(in_frame);
    }
}

void detour::setStart(float value){
    detour_start = 0 + (int)floor(value*((float)getEndFrame()));
    if(detour_position < detour_start){
        detour_position = detour_start;
        detour_position_part = (float)detour_position;
        }
}

void detour::setEnd(float value){
    int new_end = detour_start + 1 + (int)floor(value*((float)detours[current_detour].size() - detour_start -1));
    detour_end = MIN(new_end, detours[current_detour].size() - 1);
    if(detour_position > detour_end){
        detour_position = detour_end;
        detour_position_part = (float)detour_position;
        }
}

void detour::setPosition(float value){
    int new_position = detour_start + (int)floor(value*(float)getEndFrame());
    detour_position = MIN(new_position, getEndFrame());
}

void detour::setSpeed(float value){
    detour_speed = -5.0 + 10.0*value;
}

void detour::checkMemory(){
    int totalFrames = detours[0].size() + detours[1].size() + detours[2].size() + detours[3].size();
    if(totalFrames > 500){memory_full = true;}
    else{memory_full = false;}
}

int detour::getEndFrame(){
    int end = detours[current_detour].size() - 1;
    if(detour_end > 0){end = detour_end;}

    return MAX(end,0);
}

int detour::subsetMod(int amount){
    int newAmount = ( (amount - detour_start) % (getEndFrame() + 1 - detour_start) );
    if (newAmount < 0){ newAmount += getEndFrame() + 1; }
    return newAmount + detour_start;
}

float detour::subsetModFloat(float amount){
    // x mod y for a float is x - y*floor(x/y)
    float x = amount - (float)detour_start;
    float y = (float)getEndFrame() - (float)detour_start;
    return x - y*floor(x/y) + (float)detour_start;
}

