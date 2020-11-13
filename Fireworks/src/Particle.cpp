//
//  Particle.cpp
//  wk06_particle_system
//
//  Created by Tyler Henry on 10/2/18.
//

#include "Particle.hpp"

Particle::Particle()
{
    pos = glm::vec2(0,0);
    vel = glm::vec2(0,0);
   
}

Particle::Particle(glm::vec2 _pos, glm::vec2 _vel, float _angle, float _mass)
{
    pos +=vel;
    vel = _vel;
    mass = _mass;

}



void Particle::update()
{
    pos.x += glm::vec2(vel*cos(angle),vel*sin(angle));
    acc *= 0;
}

void Particle::draw()
{
    float color = ofRandom(0,200);
    ofPushStyle();
    float hue = ofMap(mass, 0, 10, 0, 255);
    ofSetColor(color,color,color);
    ofDrawCircle(pos, 9);
    ofPopStyle();
}

