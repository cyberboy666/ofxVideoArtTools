#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

    captur.setup("vidGrabber");
    // incur.setup("actionMap.json");
    detour.setup();

    string shaderPath;
    #ifdef TARGET_OPENGLES
	shaderPath = "shadersES2/";
    #else
	shaderPath = "shadersGL3/";
    #endif

    mixConjur.setup();
    mixConjur.loadShader(shaderPath + "mixShader");
    // effectConjur.setup();
    // effectConjur.loadShader(shaderPath + "effectShader");
    mixConjur.isActive = false;
    in_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    detour_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    out_fbo.allocate(ofGetWidth(), ofGetHeight());

}

//--------------------------------------------------------------
void ofApp::update(){
    captur.update();
    in_frame.setFromPixels(captur.getPixels().getData(), captur.width, captur.height, 3);
    in_frame.resize(ofGetWidth(), ofGetHeight());
    detour_frame = detour.getFrame();

    in_texture.loadData(in_frame.getData(), ofGetWidth(), ofGetHeight(), GL_RGBA);
    detour_texture.loadData(detour_frame.getData(), ofGetWidth(), ofGetHeight(), GL_RGBA);

    vector<ofTexture> mixInput = {in_texture, detour_texture};
    //out_fbo = mixConjur.apply(mixInput);
    
    // ofTexture mix_texture = mix_fbo.getTexture();
    // <ofTexture> effectInput = {mix_texture};
    // out_fbo = effectConjur.apply(effectInput);

    if(detour.is_recording){
        out_fbo.readToPixels(out_frame);
        detour.addFrame(out_frame); 
        }  
    }   

        // vector<tuple<string, string>> actionsList = incur.getActions();
        // for( int i = 0; i < actionsList.size(); i++){
        //     ofLog() << "action is " << get<0>(actionsList[i]) << "value is " << get<1>(actionsList[i]);
        // }


//--------------------------------------------------------------
void ofApp::draw(){
        // out_fbo.draw(0, 0);
        in_texture.draw(0,0,ofGetWidth(), ofGetHeight() );
    }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'r':
            detour.is_recording = !detour.is_recording;
            break;
        // case 'i':
        //     showInfo = !showInfo;
        //     break;
        case 't':
            detour.record_loop = !detour.record_loop;
            break;
        // case 'a':
        //     is_delay = !is_delay;
        //     break;
        // case 'z':
        //     delay_size --;
        //     if(delay_size < 0){delay_size = 0;}
        //     break;
        // case 'x':
        //     delay_size ++;
        //     break;
        case 'w':
            detour.is_playing = !detour.is_playing;
            break;
        case 'c':
            detour.detour_start = 0;
            detour.detour_end = 0;
            detour.detour_position_part = 0;
            detour.detour_position = 0;
            detour.detours[detour.current_detour].clear();
            break;
        case 'k':
            detour.mix_position -= 0.2;
            if(detour.mix_position < 0){detour.mix_position = 0;}
            mixConjur.shaderParams[0] = detour.mix_position;
            break;
        case 'l':
            detour.mix_position += 0.2;
            if(detour.mix_position > 1){detour.mix_position = 1;}
            mixConjur.shaderParams[0] = detour.mix_position;
            break;
        case '[':
            detour.detour_speed -= 0.2;
            if (detour.detour_speed < -3){detour.detour_speed = -3;}
            break;
        case ']':
            detour.detour_speed += 0.2;
            if (detour.detour_speed > 3){detour.detour_speed = 3;}
            break;
        case '=':
            detour.detour_speed *= -1;
            break;
        case 'v':
            detour.normStart -= 0.1;
            if (detour.normStart < 0){detour.normStart = 0;}
            detour.setStart(detour.normStart);
            break;
        case 'b':
            detour.normStart += 0.1;
            if (detour.normStart > 1){detour.normStart = 1;}
            detour.setStart(detour.normStart);
            break;
        case 'n':
            detour.normEnd -= 0.1;
            if (detour.normEnd < 0){detour.normEnd = 0;}
            detour.setEnd(detour.normEnd);
            break;
        case 'm':
            detour.normEnd += 0.1;
            if (detour.normEnd > 1){detour.normEnd = 1;}
            detour.setEnd(detour.normEnd);
            break;
        case ',':
            detour.normPosition -= 0.1;
            if (detour.normPosition < 0){detour.normPosition = 0;}
            detour.setPosition(detour.normPosition);
            break;
        case '.':
            detour.normPosition += 0.1;
            if (detour.normPosition > 1){detour.normPosition = 1;}
            detour.setPosition(detour.normPosition);
            break;
        case 'o':
            detour.detour_position = detour.subsetMod(detour.detour_position - 1);
            detour.detour_position_part = (float)detour.detour_position;
            break;
        case 'p':
            detour.detour_position = detour.subsetMod(detour.detour_position + 1);
            detour.detour_position_part = (float)detour.detour_position;
            break;
        /*
        case 'p':
            vidGrabber.setup(settings);
            //setupPiCam();
            break;
        case ' ':
            vidGrabber.close();
            break; */
        // case '<':
        //     setupMidi();
        //     break;
        case 'q':
            ofExit();
            break;
        case '0':

            detour.current_detour = 0;
            detour.detour_start = 0;
            detour.detour_end = 0;
            detour.detour_position_part = 0;
            detour.detour_position = 0;

            break;
        case '1':

            detour.current_detour = 1;
            detour.detour_start = 0;
            detour.detour_end = 0;
            detour.detour_position_part = 0;
            detour.detour_position = 0;
  
            break;
        case '2':

            detour.current_detour = 2;
            detour.detour_start = 0;
            detour.detour_end = 0;
            detour.detour_position_part = 0;
            detour.detour_position = 0;

            break;
        case '3':

            detour.current_detour = 3;
            detour.detour_start = 0;
            detour.detour_end = 0;
            detour.detour_position_part = 0;
            detour.detour_position = 0;

            break;
    }
  
}