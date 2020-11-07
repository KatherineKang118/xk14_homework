#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(30);
    // on OSX: if you want to use ofSoundPlayer together with ofSoundStream you need to synchronize buffersizes.
    // use ofFmodSetBuffersize(bufferSize) to set the buffersize in fmodx prior to loading a file.
    
    synth.load("sound/synth.wav");
    beats.load("sound/Travis Scott - NO BYSTANDERS.wav");
    vocals.load("sound/Scottybeamup Tight $wag - Trap Money.WAV");
    synth.setVolume(0.75f);
    beats.setVolume(0.75f);
    vocals.setVolume(0.5f);
    font.load("Sudbury_Basin_3D.ttf", 32);
    beats.setMultiPlay(false);
    vocals.setMultiPlay(true);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update the sound playing system:
    ofSoundUpdate();

    
   
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    // draw the background colors:
    float widthDiv = ofGetWidth() / 3.0f;

    
    
    //---------------------------------- synth:
    if (synth.isPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("synth !!", 50,50);
    
    ofSetHexColor(0x000000);
    string tempStr = "click to play\npct done: "+ofToString(synth.getPosition())+"\nspeed: " + ofToString(synth.getSpeed()) + "\npan: " + ofToString(synth.getPan()) ;
    ofDrawBitmapString(tempStr, 50,ofGetHeight()-50);
    
    
    
    //---------------------------------- beats:
    if (beats.isPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("beats !!", widthDiv+50,50);
    
    ofSetHexColor(0x000000);
    tempStr = "click and drag\npct done: "+ofToString(beats.getPosition())+"\nspeed: " +ofToString(beats.getSpeed());
    ofDrawBitmapString(tempStr, widthDiv+50,ofGetHeight()-50);
    
    //---------------------------------- vocals:
    if (vocals.isPlaying()) ofSetHexColor(0xFF0000);
    else ofSetHexColor(0x000000);
    font.drawString("vocals !!", widthDiv*2+50,50);
    
    ofSetHexColor(0x000000);
    tempStr = "click to play (multiplay)\npct done: "+ofToString(vocals.getPosition())+"\nspeed: " + ofToString(vocals.getSpeed());
    ofDrawBitmapString(tempStr, widthDiv*2+50,ofGetHeight()-50);
    
    float red=ofRandom(0,255);
    float blue=ofRandom(0,255);
    float green=ofRandom(0,255);
    float position=ofRandom(0,800);
    int numLines = 30;
    int minRadius = 25;
    int maxRadius = 50;
    for (int i=0; i<numLines; i++) {
        
        // Formula for converting from polar to Cartesian coordinates:
        //    x = cos(polar angle) * (polar distance)
        //    y = sin(polar angle) * (polar distance)
        // We need our angle to be in radians if we want to use sin() or cos()
        // so we can make use of an openFrameworks function to convert from degrees
        // to radians
        float angle = ofRandom(ofDegToRad(360.0));
        float distance = ofRandom(minRadius, maxRadius);
        float xOffset = cos(angle) * distance;
        float yOffset = sin(angle) * distance;
        
        float alpha = ofMap(distance, minRadius, maxRadius, 50, 0); // Make shorter lines more opaque
        ofSetColor(red, green, blue, alpha);
        
        ofSetLineWidth(ofRandom(1.0, 5.0)); // Remember, this doesn't work on all graphics cards
        ofLine(100, 700, position+xOffset, 800+yOffset);
        ofLine(150, 550, position+xOffset, 800+yOffset);
        ofLine(200, 350, position+xOffset, 800+yOffset);
        ofLine(400, 100, position+xOffset, 800+yOffset);
        ofLine(600, 150, position+xOffset, 800+yOffset);
        ofLine(700, 400, position+xOffset, 800+yOffset);
        ofLine(800, 650, position+xOffset, 800+yOffset);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // continuously control the speed of the beat sample via drag,
    // when in the "beat" region:
    float widthStep = ofGetWidth() / 3.0f;
    if (x >= widthStep && x < widthStep*2){
        beats.setSpeed( 0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float widthStep = ofGetWidth() / 3.0f;
    if (x < widthStep){
        synth.play();
        synth.setSpeed( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*10);
        synth.setPan(ofMap(x, 0, widthStep, -1, 1, true));
    } else if (x >= widthStep && x < widthStep*2){
        beats.play();
    } else {
        vocals.play();
        vocals.setSpeed( 0.1f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*3);
        //map x within the last third of window to -1 to 1 ( for left / right panning )
        vocals.setPan( ofMap(x, widthStep*2, widthStep*3, -1, 1, true) );
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
