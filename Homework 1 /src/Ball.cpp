#include "Ball.h"

// constructor
Ball::Ball() {

	// inside the constructor you initialize the object's variables

	// random radius between 40 and 100
	radius = ofRandom(40,100);

	// random color
	float red	= ofRandom(0,250);
	float green	= ofRandom(0,100);
	float blue	= ofRandom(0,200);
	color = ofColor(red, green, blue);

	// random position in window
	x = ofRandom(radius, ofGetWidth()  - radius);
	y = ofRandom(radius, ofGetHeight() - radius);

	// random x and y speeds/directions between -20 and 20
	dirX = ofRandom(-20,20);
	dirY = ofRandom(-20,20);
}

// update position, etc.
void Ball::update() {

	x+=dirX;	// move along x by amount of dirX
	y+=dirY;	// move along y by amount of dirY

	// check for bounces at edges of window:

	// check left
	if (x <= radius) {
		x = radius;			// set the position back to the edge of window
		dirX = -dirX;		// and reverse direction
	}
	// check right
	else if (x >= ofGetWidth() - radius) {
		x = ofGetWidth() - radius;			// similar to above
		dirX = -dirX;
	}

	// check top and bottom
	if (y <= radius) {
		y = radius;
		dirY = -dirY;
	}
	else if (y >= ofGetHeight() - radius) {
		y = ofGetHeight() - radius;
		dirY = -dirY;
	}
}


// draw the ball
void Ball::draw() {

	ofSetColor(color);				// set the GLOBAL color
	ofDrawCircle(x,y, radius);		// and draw
}
