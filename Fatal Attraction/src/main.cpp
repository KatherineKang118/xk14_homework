#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(793, 530,OF_WINDOW);			// <-------- setup the GL context
    ofRunApp(new ofApp());
    ofSetupOpenGL(800,800,OF_WINDOW);
}
