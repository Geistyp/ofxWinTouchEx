#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

	touchEx.setup();

	ofAddListener(touchEx.eventPan, this, &ofApp::gestureMove);
	ofAddListener(touchEx.eventZoom, this, &ofApp::gestureZoom);
	ofAddListener(touchEx.eventRotate, this, &ofApp::gestureRotate);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

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

void ofApp::gestureMove(ofVec2f & v)
{
	cout << "Move:" << v << endl;
}

void ofApp::gestureZoom(ofVec3f & v)
{
	cout << "Zoom:" << v << endl;
}

void ofApp::gestureRotate(float& v)
{
	cout << "Rotate:" << v << endl;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
