#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    image.load("universe.jpg");
    
    
    ofDisableArbTex();
    
    bWireframe  = false;
    bFill       = true;
    bDrawNormals= false;
    bDrawAxes   = false;
    bDrawLights = false;
    bHelpText   = false;
    bMousePressed   = false;
    bSplitFaces = false;
    
    float width     = ofGetWidth() * .12;
    float height    = ofGetHeight() * .12;
   
    plane.set( width*3.0, height*1.25 );
    sphere.setRadius( width*0.65 );
    icoSphere.setRadius( width*0.85 );
    
    mode = 0;
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.55, .35, .75) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    ofSetSphereResolution(24);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );

}

//--------------------------------------------------------------
void ofApp::draw(){
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    image.draw(0,0);
    if (bMousePressed) {
        spinX = spinY = 0.0f;
    }
    
    cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
    cam.begin();
    
    ofEnableDepthTest();
    
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
    
    float screenWidth = ofGetWidth();
    float screenHeight = ofGetHeight();
    
    
    sphere.setPosition(    -screenWidth * .5 + screenWidth *  3/4.f, screenHeight *  1.1/6.f, 0);
    icoSphere.setPosition( -screenWidth * .5 + screenWidth *  1/4.f, screenHeight * -1.1/6.f, 0);
   
    // Plane //
    
    plane.rotateDeg(spinX, 1.0, 0.0, 0.0);
    plane.rotateDeg(spinY, 0, 1.0, 0.0);
    
    
    
    if (mode == 3) {
        deformPlane = plane.getMesh();
        // x = columns, y = rows //
        glm::vec2 planeDims = plane.getResolution();
        float planeAngleX = ofGetElapsedTimef()*3.6;
        float planeAngleInc = 3.f / (float)planeDims.x;
        glm::vec3 vert;
        for (size_t i = 0; i < deformPlane.getNumIndices(); i++) {
            planeAngleX += planeAngleInc;
            int ii = deformPlane.getIndex(i);
            vert = deformPlane.getVertex(ii);
            vert.z += cos(planeAngleX) * 50;
            deformPlane.setVertex(ii, vert);
        }
    }
    
    if (!bFill && bWireframe) {
        // if we are only drawing the wireframe, use
        // the material to draw it, otherwise the material
        // will be bound and unbound for every geometry
        // and the wireframe will be drawn in black
        material.begin();
    }
    
    if (bFill) {
        material.begin();
        ofFill();
        if (mode == 3) {
            plane.transformGL();
            deformPlane.draw();
            plane.restoreTransformGL();
        }
        else {
            plane.draw();
        }
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        plane.setPosition(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z + 1);
        plane.drawWireframe();
        plane.setPosition(plane.getPosition().x, plane.getPosition().y, plane.getPosition().z - 1);
        
    }
    
    // Box //
    
    box.rotateDeg(spinX, 1.0, 0.0, 0.0);
    box.rotateDeg(spinY, 0, 1.0, 0.0);
    
    if (bFill) {
        material.begin();
        ofFill();
        if (mode == 3) {
            box.transformGL();
            for (int i = 0; i < ofBoxPrimitive::SIDES_TOTAL; i++) {
                ofPushMatrix();
                ofTranslate(boxSides[i].getNormal(0) * sin(ofGetElapsedTimef()) * 50);
                boxSides[i].draw();
                ofPopMatrix();
            }
            box.restoreTransformGL();
        }
        else {
            box.draw();
        }
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        box.setScale(1.01f);
        box.drawWireframe();
        box.setScale(1.f);
    }
    
    
    // Sphere //
    sphere.rotateDeg(spinX, 1.0, 0.0, 0.0);
    sphere.rotateDeg(spinY, 0, 1.0, 0.0);
    
    if (mode == 3) {
        sphere.setMode(OF_PRIMITIVE_TRIANGLES);
        triangles = sphere.getMesh().getUniqueFaces();
    }
    
    if (bFill) {
        material.begin();
        ofFill();
        if (mode == 3) {
            float angle = ofGetElapsedTimef()*3.2;
            float strength = (sin(angle + .25)) * .5f * 5.f;
            glm::vec3 faceNormal;
            for (size_t i = 0; i < triangles.size(); i++) {
                // store the face normal here.
                // we change the vertices, which makes the face normal change
                // every time that we call getFaceNormal //
                faceNormal = triangles[i].getFaceNormal();
                for (int j = 0; j < 3; j++) {
                    triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * strength);
                }
            }
            sphere.getMesh().setFromTriangles(triangles);
        }
        sphere.draw();
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        sphere.setScale(1.01f);
        sphere.drawWireframe();
        sphere.setScale(1.f);
    }
    
    
    // ICO Sphere //
    
    icoSphere.rotateDeg(spinX, 1.0, 0.0, 0.0);
    icoSphere.rotateDeg(spinY, 0, 1.0, 0.0);
    
    if (mode == 3) {
        triangles = icoSphere.getMesh().getUniqueFaces();
    }
    
    if (bFill) {
        material.begin();
        ofFill();
        
        if (mode == 3) {
            float angle = (ofGetElapsedTimef() * 1.4);
            glm::vec3 faceNormal;
            for (size_t i = 0; i < triangles.size(); i++) {
                float frc = ofSignedNoise(angle* (float)i * .1, angle*.05) * 4;
                faceNormal = triangles[i].getFaceNormal();
                for (int j = 0; j < 3; j++) {
                    triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * frc);
                }
            }
            icoSphere.getMesh().setFromTriangles(triangles);
        }
        
        icoSphere.draw();
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        icoSphere.setScale(1.01f);
        icoSphere.drawWireframe();
        icoSphere.setScale(1.f);
    }
    
    
    // Cylinder //
    if (mode == 3) {
        topCap = cylinder.getTopCapMesh();
        bottomCap = cylinder.getBottomCapMesh();
        body = cylinder.getCylinderMesh();
    }
    
    cylinder.rotateDeg(spinX, 1.0, 0.0, 0.0);
    cylinder.rotateDeg(spinY, 0, 1.0, 0.0);
    if (bFill) {
        material.begin();
        ofFill();
        if (mode == 3) {
            cylinder.transformGL();
            ofPushMatrix(); {
                if (topCap.getNumNormals() > 0) {
                    ofTranslate(topCap.getNormal(0) * (cos(ofGetElapsedTimef() * 5) + 1)*.5f * 100);
                    topCap.draw();
                }
            } ofPopMatrix();
            ofPushMatrix(); {
                if (bottomCap.getNumNormals() > 0) {
                    ofTranslate(bottomCap.getNormal(0) * (cos(ofGetElapsedTimef() * 4) + 1)*.5f * 100);
                    bottomCap.draw();
                }
            } ofPopMatrix();
            ofPushMatrix(); {
                float scale = (cos(ofGetElapsedTimef() * 3) + 1)*.5f + .2;
                ofScale(scale, scale, scale);
                body.draw();
            } ofPopMatrix();
            cylinder.restoreTransformGL();
        }
        else {
            cylinder.draw();
        }
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        cylinder.setScale(1.01f);
        cylinder.drawWireframe();
        cylinder.setScale(1.0f);
    }
    
    
    // Cone //
    cone.rotateDeg(spinX, 1.0, 0.0, 0.0);
    cone.rotateDeg(spinY, 0, 1.0, 0.0);
    
    if (mode == 3) {
        bottomCap = cone.getCapMesh();
        body = cone.getConeMesh();
    }
    if (bFill) {
        material.begin();
        ofFill();
        if (mode == 3) {
            cone.transformGL();
            ofPushMatrix();
            if (bottomCap.getNumNormals() > 0) {
                ofTranslate(bottomCap.getNormal(0) * cone.getHeight()*.5);
                ofRotateDeg(sin(ofGetElapsedTimef() * 5) * RAD_TO_DEG, 1, 0, 0);
                bottomCap.draw();
            }
            ofPopMatrix();
            
            ofPushMatrix();
            ofRotateDeg(90, 1, 0, 0);
            ofRotateDeg((cos(ofGetElapsedTimef() * 6) + 1)*.5 * 360, 1, 0, 0);
            body.draw();
            ofPopMatrix();
            cone.restoreTransformGL();
        }
        else {
            cone.draw();
        }
        material.end();
    }
    
    if (bWireframe) {
        ofNoFill();
        ofSetColor(0, 0, 0);
        cone.setScale(1.01f);
        cone.drawWireframe();
        cone.setScale(1.0f);
    }
    
    if (!bFill && bWireframe) {
        material.end();
    }
    
    if (mode == 1 || mode == 3) texture.getTexture().unbind();
    if (mode == 2) vidGrabber.getTexture().unbind();
    
    material.end();
    ofDisableLighting();
    
    if (bDrawLights) {
        ofFill();
        ofSetColor(pointLight.getDiffuseColor());
        pointLight.draw();
        ofSetColor(pointLight2.getDiffuseColor());
        pointLight2.draw();
        ofSetColor(pointLight3.getDiffuseColor());
        pointLight3.draw();
    }
    
    if (bDrawNormals) {
        ofSetColor(225, 0, 255);
        plane.drawNormals(20, bSplitFaces);
        box.drawNormals(20, bSplitFaces);
        sphere.drawNormals(20, bSplitFaces);
        icoSphere.drawNormals(20, bSplitFaces);
        cylinder.drawNormals(20, bSplitFaces);
        cone.drawNormals(20, bSplitFaces);
    }
    if (bDrawAxes) {
        plane.drawAxes(plane.getWidth()*.5 + 30);
        box.drawAxes(box.getWidth() + 30);
        sphere.drawAxes(sphere.getRadius() + 30);
        icoSphere.drawAxes(icoSphere.getRadius() + 30);
        cylinder.drawAxes(cylinder.getHeight() + 30);
        cone.drawAxes(cone.getHeight() + 30);
    }
    
    ofDisableDepthTest();
    
    ofFill();
    
    cam.end();
   

    

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
