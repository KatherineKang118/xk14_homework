#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        ofSetWindowShape(600, 800);
        ofEnableAntiAliasing(); // This is enabled by default
    ofSetCircleResolution(50); // For smoother looking circles + ellipses
}

//--------------------------------------------------------------
void ofApp::update(){
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
        ofBackground(0); // Clear the screen with a black color
    
    
    
    ofFill(); // If we omit this and leave ofNoFill(), all the shapes will be outlines!
    ofSetLineWidth(2); // Line width is a default value of 1 if you don't modify it
    float dist=abs(((ofGetMouseY()-300)*0.5+ofGetMouseX()-400*0.5)*0.1);
    // Draw some shapes
    ofSetColor(0,0,255);
    ofCircle(250, 300, 50);
    ofCircle(350, 300, 50); // Radius of 50, centered at (250, 100)
    ofSetColor(255,255,0,dist);
    ofEllipse(300, 400, 400, 600); // 80 wide x 100 high, centered at (400 100)
    ofSetColor(200,0,0,dist);
    ofRect(260, 320, 80, 180);
    ofSetColor(255,0,255,80);
    ofEllipse(300, 600, 150, 100);
    
    // If you are curious how to generate the series of lines shown in figure 2, you can use a for loop:
    //for (int i=0; i<11; i++) {
    //    ofLine(650, 50+(i*10), 750, 75+(i*5));
    //}
    
    
    // Draw some shapes (shifted down 150 pixels)
   
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
