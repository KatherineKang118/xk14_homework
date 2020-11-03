//
//  triangle.cpp
//  xk14 Xiaoyin Kang
//
//  Created by 颜昕 on 11/1/20.
//

#include "triangle.hpp"
triangleBall::triangleBall() {
    
    // nothing needed here, because all variables are initialized in parent Ball class
}

void triangleBall::draw() {
    
    ofSetColor(color);    // the color carries over from the parent Ball class
    
    float sqX = x - radius; // rectangles draw from the top left corner unlike circles (which draw from the center), so we need to compensate
    float sqY = y - radius;
    ofDrawTriangle(x, y, x+radius,y+radius*1.732, x+radius+radius,y);  // width and height will both be double the radius
}

