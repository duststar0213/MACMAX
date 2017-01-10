#include "ofApp.h"

//void ofApp::drawMarker(float size, const ofColor & color){
void ofApp::drawMarker(float size){
    /*ofDrawAxis(size);
    ofPushMatrix();
    // move up from the center by size*.5
    // to draw a box centered at that point
    ofTranslate(0,size*0.5,0);
    ofFill();
    ofSetColor(color,50);
    ofDrawSphere(size);
    ofNoFill();
    ofSetColor(color);
    ofDrawSphere (size);
    ofPopMatrix();*/
    
    //ofDrawAxis(size);
    ofPushMatrix();
    //ofSetColor(color);
    // move up from the center by size*.5
    // to draw a box centered at that point
    //ofTranslate(0,size*0.5,0);
    //ofFill();
    //texture.bind(); // thwe
    movie.getTexture().bind();
    plane.draw();
    //texture.unbind();
    movie.getTexture().unbind();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    useVideo = false;
    string boardName = "boardConfiguration.yml";
    
    if(useVideo){
        player.load("videoboard.mp4");
        player.play();
        video = &player;
    }else{
        grabber.setDeviceID(0);
        grabber.initGrabber(640,480);
        video = &grabber;
    }
    
    //aruco.setThreaded(false);
    aruco.setup("intrinsics.int", video->getWidth(), video->getHeight(), boardName);
    aruco.getBoardImage(board.getPixels());
    board.update();
    
    showMarkers = true;
    showBoard = true;
    showBoardImage = false;
    
    ofEnableAlphaBlending();
    ofDisableArbTex();
    //img.load("test2.jpg");
    movie.load("glitchandself.mp4");
    movie.play();
   //texture=img.getTexture();
    texture=movie.getTexture();
    //texture.setTextureWrap(GL_REPEAT,GL_REPEAT );
 
    
 
    
    //img.loadData(test1.getPixels());
    //test1.update();
   // movie.update();
    
    // position planes
    plane.set(.17, .17);   ///dimensions for width and height in pixels
    plane.setPosition(0, 0, 0); /// position in x y z
    plane.rotate(90.0, ofVec3f(1,0,0));
    plane.setResolution(2, 2); /// this resolution (as columns and rows) is enough

}

//--------------------------------------------------------------
void ofApp::update(){
    //handle the example
    video->update();
    if(video->isFrameNew()){
        aruco.detectBoards(video->getPixels());
    }
    
    //handle my video texture
    movie.update();
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    video->draw(0,0,ofGetWidth(),ofGetHeight());
    
    //aruco.draw();
    
    if(showMarkers){
        for(int i=0;i<aruco.getNumMarkers();i++){
            aruco.begin(i);
            drawMarker(0.15);
            aruco.end();
        }
    }
    
    
    if(showBoard && aruco.getBoardProbability()>0.03){
        for(int i=0;i<aruco.getNumBoards();i++){
            aruco.beginBoard(i);
            drawMarker(ofRandom(.5));
            aruco.end();
        }
    }
    
    
    ofSetColor(255);
    if(showBoardImage){
        board.draw(ofGetWidth()-320,0,320,320*float(board.getHeight())/float(board.getWidth()));
    }
    ofDrawBitmapString("markers detected: " + ofToString(aruco.getNumMarkers()),20,20);
    ofDrawBitmapString("fps " + ofToString(ofGetFrameRate()),20,40);
    ofDrawBitmapString("m toggles markers",20,60);
    ofDrawBitmapString("b toggles board",20,80);
    ofDrawBitmapString("i toggles board image",20,100);
    ofDrawBitmapString("s saves board image",20,120);
    ofDrawBitmapString("0-9 saves marker image",20,140);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='m') showMarkers = !showMarkers;
    if(key=='b') showBoard = !showBoard;
    if(key=='i') showBoardImage = !showBoardImage;
    if(key=='s') board.save("boardimage.png");
    if(key>='0' && key<='9'){
        // there's 1024 different markers
        int markerID = key - '0';
        aruco.getMarkerImage(markerID,240,marker);
        marker.save("marker"+ofToString(markerID)+".png");
    }

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
