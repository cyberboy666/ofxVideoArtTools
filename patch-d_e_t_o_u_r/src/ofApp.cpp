#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

    captur.setup("vidGrabber");
    ofSetFrameRate(captur.framerate);
    incur.setupThis("actionMap.json");
    detour.setup();

    effectParams = {0, 0, 0, 0};

    string shaderPath;
    #ifdef TARGET_OPENGLES
	shaderPath = "shadersES2/";
    #else
	shaderPath = "shadersGL3/";
    #endif

    mixConjur.setup();
    mixConjur.loadShader(shaderPath + "mixShader");
    effectConjur.setup();
    effectConjur.loadShader(shaderPath + "effectShader");
    // mixConjur.isActive = false;
    in_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    detour_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    
    out_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    mix_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

}

//--------------------------------------------------------------
void ofApp::update(){
    captur.update();
    in_frame.setFromPixels(captur.getPixels().getData(), captur.width, captur.height, 3);
    in_frame.resize(ofGetWidth(), ofGetHeight());
    detour_frame = detour.getFrame();

    in_texture.loadData(in_frame.getData(), in_frame.getWidth(), in_frame.getHeight(), GL_RGB);
    detour_texture.loadData(detour_frame.getData(), detour_frame.getWidth(), detour_frame.getHeight(), GL_RGB);

    vector<ofTexture> mixInput = {in_texture, detour_texture};
    mix_fbo = mixConjur.apply(mixInput);
    
    ofTexture mix_texture = mix_fbo.getTexture();
    vector<ofTexture> effectInput = {mix_texture};
    out_fbo = effectConjur.apply(effectInput);

    if(detour.is_recording){
        out_fbo.readToPixels(out_frame);
        detour.addFrame(out_frame); 
        }  

        vector<vector<string>> actionsList = incur.getActions();
        for( int i = 0; i < actionsList.size(); i++){
            ofLog() << "action is " << actionsList[i][0] << "value is " << actionsList[i][1];
            runAction(actionsList[i][0], actionsList[i][1]);
        }
}

//--------------------------------------------------------------
void ofApp::draw(){
        out_fbo.draw(0, 0);
        detour.printState();
    }

 void ofApp::runAction(string action, string amount){
     if(action == "togglePlay"){ togglePlay();}
     else if(action == "somethingElse"){}
 }

void ofApp::togglePlay(){
    detour.is_playing = !detour.is_playing;
    
}
void ofApp::toggleRecord(){
    detour.is_recording = !detour.is_recording;
}
void ofApp::toggleRecordMode(){
    detour.record_loop = !detour.record_loop;
}
void ofApp::toggleShowState(){
    detour.showInfo = !detour.showInfo;
    }
void ofApp::setSpeed(float normValue){
    detour.setSpeed(normValue);
}
void ofApp::clearThisDetour(){
    detour.detour_start = 0;
    detour.detour_end = 0;
    detour.detour_position_part = 0;
    detour.detour_position = 0;
    detour.detours[detour.current_detour].clear();
}
void ofApp::setPosition(float normValue){
    detour.setPosition(normValue);
}
void ofApp::setSpeedIfPlayingElsePosition(float normValue){
    if(detour.is_playing){ detour.setSpeed(normValue);  }
    else { detour.setPosition(normValue); }
}

void ofApp::setMixPosition(float normValue){
    detour.mix_position = normValue;
    if(detour.mix_position < 0){detour.mix_position = 0;}
    else if(detour.mix_position > 1){detour.mix_position = 1;}
    mixConjur.shaderParams[0] = detour.mix_position;
}
void ofApp::setStartPosition(float normValue){
    detour.setStart(normValue);
}
void ofApp::setEndPosition(float normValue){
    detour.setEnd(normValue);
}
void ofApp::switchDetour0(){
    detour.current_detour = 0;
    detour.detour_start = 0;
    detour.detour_end = 0;
    detour.detour_position_part = 0;
    detour.detour_position = 0;
}
void ofApp::switchDetour1(){
    detour.current_detour = 1;
    detour.detour_start = 0;
    detour.detour_end = 0;
    detour.detour_position_part = 0;
    detour.detour_position = 0;
}
void ofApp::switchDetour2(){
    detour.current_detour = 2;
    detour.detour_start = 0;
    detour.detour_end = 0;
    detour.detour_position_part = 0;
    detour.detour_position = 0;
}
void ofApp::switchDetour3(){
    detour.current_detour = 3;
    detour.detour_start = 0;
    detour.detour_end = 0;
    detour.detour_position_part = 0;
    detour.detour_position = 0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    incur.onKeyPress(key);
//     switch(key){
//         case 'r':
//             toggleRecord();
//             break;
//         case 'i':
//             toggleShowState();
//             break;
//         case 't':
//             toggleRecordMode();
//             break;
//         // case 'a':
//         //     is_delay = !is_delay;
//         //     break;
//         // case 'z':
//         //     delay_size --;
//         //     if(delay_size < 0){delay_size = 0;}
//         //     break;
//         // case 'x':
//         //     delay_size ++;
//         //     break;
//         case 'w':
//             togglePlay();
//             break;
//         case 'c':
//             clearThisDetour();
//             break;
//         case 'k':
//             setMixPosition(detour.mix_position - 0.2);
//             break;
//         case 'l':
//             setMixPosition(detour.mix_position + 0.2);
//             break;
//         case '[':
//             detour.detour_speed -= 0.2;
//             break;
//         case ']':
//             detour.detour_speed += 0.2;
//             break;
//         case '=':
//             detour.detour_speed *= -1;
//             break;
//         case 'v':
//             detour.normStart -= 0.1;
//             if (detour.normStart < 0){detour.normStart = 0;}
//             detour.setStart(detour.normStart);
//             break;
//         case 'b':
//             detour.normStart += 0.1;
//             if (detour.normStart > 1){detour.normStart = 1;}
//             detour.setStart(detour.normStart);
//             break;
//         case 'n':
//             detour.normEnd -= 0.1;
//             if (detour.normEnd < 0){detour.normEnd = 0;}
//             detour.setEnd(detour.normEnd);
//             break;
//         case 'm':
//             detour.normEnd += 0.1;
//             if (detour.normEnd > 1){detour.normEnd = 1;}
//             detour.setEnd(detour.normEnd);
//             break;
//         case ',':
//             detour.normPosition -= 0.1;
//             if (detour.normPosition < 0){detour.normPosition = 0;}
//             detour.setPosition(detour.normPosition);
//             break;
//         case '.':
//             detour.normPosition += 0.1;
//             if (detour.normPosition > 1){detour.normPosition = 1;}
//             detour.setPosition(detour.normPosition);
//             break;
//         case 'o':
//             detour.detour_position = detour.subsetMod(detour.detour_position - 1);
//             detour.detour_position_part = (float)detour.detour_position;
//             break;
//         case 'p':
//             detour.detour_position = detour.subsetMod(detour.detour_position + 1);
//             detour.detour_position_part = (float)detour.detour_position;
//             break;
//         case 'q':
//             ofExit();
//             break;
//         case '0':
//             switchDetour0();
//             break;
//         case '1':
//             switchDetour1();
//             break;
//         case '2':
//             switchDetour2();
//             break;
//         case '3':
//             switchDetour3();
//             break;
//         case '4':
//             effectParams[0] = effectParams[0] + 0.2 - floor(effectParams[0] + 0.2);
//             effectConjur.shaderParams[0] = effectParams[0];
//             break;
//         case '5':
//             effectParams[1] = effectParams[1] + 0.2 - floor(effectParams[1] + 0.2);
//             effectConjur.shaderParams[1] = effectParams[1];
//             break;
//         case '6':
//             effectParams[2] = effectParams[2] + 0.2 - floor(effectParams[2] + 0.2);
//             effectConjur.shaderParams[2] = effectParams[2];
//             break;
//     }
}