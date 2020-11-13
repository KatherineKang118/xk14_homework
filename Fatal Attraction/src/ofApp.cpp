#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    image.load("bulldogcatholic-fr-mike-schmitz-falling-in-love-with-married-man.jpg");
   
    ofSetCircleResolution(48);  // draw nicer circles
    
    // create a grid of Movers
    
    for (int y=0; y<10; y++) {          // 10 columns
        for (int x=0; x<10; x++) {      // 10 rows
            
            float posX = ofMap(x, 0, 7, 0, ofGetWidth());
            float posY = ofMap(y, 0, 7, 0, ofGetHeight());
            
            Mover mover( glm::vec2(posX, posY) );       // create the mover / set its position
            
            mover.mass = ofMap( x*y, 0, 100, 8, 15);     // new! assign a mass based on grid order
            
            movers.push_back(mover);
        }
    }
    
    attractionOn = true;
    repulsionOn  = true;
    elasticOn    = true;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // make a ball follow the mouse
    
    ofVec2f mouse;
    mouse.x = ofGetMouseX();
    mouse.y = ofGetMouseY();
    
    float pct = .05; // every frame move ball 5% towards the mouse
    
    ball = ball * (1.-pct) + mouse * pct;
    
    
    // change the ball brightness with distance
    
    float dist = mouse.distance(ball);
    
    // as distance increases, brightness increases:
    brightness = ofMap(dist, 0, 500, 50, 255);
    
    // Movers are attracted to or repulsed by the mouse, depending on their distance from it
    
    glm::vec2 mousePos = glm::vec2( ofGetMouseX(), ofGetMouseY() );
    
    for (int i=0; i<movers.size(); i++){
        
        
        // find the vector and distance to mouse
        glm::vec2 target    = mousePos - movers[i].pos;     // vector mover --to--> mouse
        float distance      = glm::length(target);          // distance = length of vector
        
        
        // too close - repulse
        if (repulsionOn && distance != 0 && distance < 100) {
            
            glm::vec2 direction = target / distance;         // normalize vector (divide by length -> length = 1)
            movers[i].applyForce(-direction);                // repulse - invert direction ( * -1 )
        }
        
        // within range - attract
        else if (attractionOn && distance != 0 && distance < 200) {
            
            glm::vec2 direction = target / distance;         // normalize
            movers[i].applyForce(direction);                 // attract, push in direction
        }
        
        if (elasticOn) {
            movers[i].applyElasticForce(0.5);       // push mover back to its original point over time
        }
        movers[i].applyDampingForce(0.2);       // add some "drag" to the Mover (slow it down)
        movers[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    image.draw(0,0);
    ofSetColor(brightness);
    ofDrawCircle(ball, 50);
    ofSetColor(255,100,250);    // reset draw color
    
    for (int i=0; i<movers.size(); i++)
    {
        movers[i].draw();
        
        // print the current elastic force on the Mover:
        // ofDrawBitmapStringHighlight(ofToString(movers[i].elasticForce, 2), movers[i].pos);
    }
    
    
    // draw the forces:
    
    if (ofGetMousePressed()){
        // ofNoFill();   // un-comment to draw outlines only
        
        
        if (attractionOn){
            // draw mouse attraction radius in green
            ofSetColor( ofColor(190,120,220, 80) );     // 80 = alpha
            ofDrawCircle(mouseX, mouseY, 200);
        }
        if (repulsionOn){
            // draw mouse repulsion radius in red
            ofSetColor( ofColor(255,127,127, 80) );
            ofDrawCircle(mouseX, mouseY, 100);
        }
        if (elasticOn){
            // draw lines from movers to their origins in yellow
            ofSetColor( ofColor(255,220,100) );
            for (int i=0; i < movers.size(); i++){
                ofDrawLine( movers[i].pos, movers[i].origPos);
            }
        }
        // ofFill();
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
