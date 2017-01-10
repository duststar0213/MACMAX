#include "ofApp.h"
#include <iostream>
#include <GLUT/GLUT.h> // use THE OPENGL UTILITY TOOLKIT BECAUSE IT CONTAINS THE
// ANGLE OF CAMERA AND SHAPES
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(false);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetBackgroundColor(190);
    //glNewList(1, GL_COMPILE);
    //glutSolidCube(5);
    //glEndList();
    
    boidNum = 100;
    target = ofVec3f(0, 0, 0);
    
    for (int i = 0; i < boidNum; i++)
    {   glNewList(1, GL_COMPILE);
        glutSolidCube(2);
        glEndList();
        SteeredParticle v(ofRandom(100)-9, ofRandom(100)-50, ofRandom(100)-50);
        v.maxForce = 8.0f;
        v.inSightDist = 60.0f;
        boids.push_back(v);
    }
    
    cam.setDistance(20);
    
    GLfloat color[] = { 1.0, 0.2, 0.2 };
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
   
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
    
   
    
    
}



//--------------------------------------------------------------
void ofApp::update(){
    for (int i =0; i <boidNum; i++)
    {
        
        
        boids[i].flock(boids);
        boids[i].update();
        boids[i].wrap(80, 100, 100);
    }
    


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    cam.begin();
    
    for (int i = boidNum; i > 0; i--)
    {
        glPushMatrix();
        glTranslatef(boids[i].position.x+i, boids[i].position.y, boids[i].position.z);
        
        GLfloat color[] = { ofRandom(0.9), ofRandom(0.9), 0.9, 0.5 };
        
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
        glCallList(1);
        glPopMatrix();
    }
    
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
