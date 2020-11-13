#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    ofSetFrameRate(60); // Limit the speed of our program to 60 frames per second
    
    ofSetBackgroundAuto(false); // Stop the background from being redrawn each frame
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    
}

//--------------------------------------------------------------
void ofApp::update(){
     particle.update();
 }


//--------------------------------------------------------------
void ofApp::draw(){
    if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
        ofBackground(0);
    }
    if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
        glm::vec2 mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
        
        int num = ofRandom(15,50);
        float length= ofRandom(40,70);
        int ccolor = ofRandom(180,200);
        for (int i=0; i<num; i++) {
            
            // Formula for converting from polar to Cartesian coordinates:
            //    x = cos(polar angle) * (polar distance)
            //    y = sin(polar angle) * (polar distance)
            // We need our angle to be in radians if we want to use sin() or cos()
            // so we can make use of an openFrameworks function to convert from degrees
            // to radians
            float angle = ofRandom(ofDegToRad(360.0));
            float time = ofGetElapsedTimef();
            float ccolor = ofRandom(0,200);
            float alpha = ofMap(length,length-10, length, 50, 0); // Make shorter lines more opaque
            float xOffset= length*cos(angle);
            float yOffset= length*sin(angle);
            ofSetColor(ccolor,ccolor,ccolor, alpha);
            particle.draw();
    

            ofSetLineWidth(ofRandom(1.0, 10.0)); // Remember, this doesn't work on all graphics cards
            ofLine(ofGetMouseX(), ofGetMouseY(), ofGetMouseX()+xOffset, ofGetMouseY()+yOffset);
        }
    }
    
    // If the right mouse button is pressed...
    if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
        ofBackground(0);  // Erase the screen with a black background
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
