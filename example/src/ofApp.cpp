#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // import RGB
    swatch.load("swatches/AdobeColor A Bar at the Folies-Bergere - Edouard Manet.ase");
    
    // import CMYK
    // swatch.load("swatches/Adobe Illustrator Metals.ase");
    
    // import Grayscale
    // swatch.load("swatches/Grays.ase");
    
    /*
     Note: loading a file into a swatch will add the colors and
     groups from that file, not replace those already there.
     To clear a swatch, use .clear()
    */
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    int numberOfColors = swatch.getAllColors().size();
    float interval = ofGetWidth() / ((float) numberOfColors);

    int i = 0;
    for(auto namedColor : swatch.getAllColors()){
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
