//
//  mover.cpp
//  NOC_1_7_motion101
//
//  Created by Firm Read on 2/22/13.
//
//

#include "mover.h"

void mover::setup(float m, float x, float y){
    mass = m;
    location.set(x,y);
    velocity.set(0,0);
    acceleration.set(0,0);
}

void mover::applyForce(ofPoint force){
    ofPoint f;
    f = force/mass;
    acceleration += f;
}

void mover::update(){
    float acc=ofRandom(-0.5,0.5);
    velocity += acceleration;
    location += velocity;
    acceleration *= acc;
}

void mover::display(){
    float ccolor=ofRandom(50,200);
    float alpha=ofRandom(80,100);
    ofSetColor(ccolor,0,ccolor,alpha);
    ofDrawCircle(location.x, location.y, mass*8);
    


}

void mover::checkEdges(){
    if (location.x > ofGetWidth()) {
        location.x = ofGetWidth()-10;
        velocity.x *= -1;
    }
    else if (location.x < 0){
        velocity.x *= -1;
        location.x = 10;
    }
    
    if (location.y > ofGetHeight()) {
        velocity.y *= -1;
        location.y = ofGetHeight()-10;
    }
    if (location.y <0) {
        velocity.y *= -1;
        location.x = 10;
        ofDrawCircle(location.x, location.y, mass*10);
    }
}
