#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    swatch_with_names.load("swatches/Groton.ase");
    swatch_with_names.load("swatches/Grays.ase");
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    int numberOfColors = swatch_with_names.getAllColors().size();
    float interval = ofGetWidth() / ((float) numberOfColors);
    
    int i = 0;
    for(auto namedColor : swatch_with_names.getAllColors()){
        ofSetColor(namedColor);
        ofDrawRectangle(interval * i++, 0, interval, ofGetHeight());
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
