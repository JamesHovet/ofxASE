#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Load every swatch from the /bin/data/swatches directory
    auto dir = ofDirectory("./swatches");
    for( auto f : dir.getSorted()){
        ofxASE swatch = ofxASE();
        swatch.load(f.path());
        swatches.push_back(swatch);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofxASE swatch = swatches[swatchIndex];
    ofxASE::NamedColorGroup group = swatch.getGroups()[groupIndex];
    
    int numberOfColors = group.getColors().size();
    float interval = ofGetWidth() / ((float) numberOfColors);
    
    int i = 0;
    for(auto namedColor : group.getColors()){
        ofSetColor(namedColor);
        ofDrawRectangle(interval * i++, 0, interval, ofGetHeight());
    }
    
    ofDrawBitmapStringHighlight(group.name, 20.0, 20.0);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == OF_KEY_RIGHT || key == ' '){
        if(swatchIndex < swatches.size() - 1){
            auto currentSwatch = swatches[swatchIndex];
            auto currentGroup = currentSwatch.getGroups()[groupIndex];
            if(groupIndex < currentSwatch.getGroups().size() - 1){
                groupIndex++;
            } else {
                swatchIndex++;
                groupIndex = 0;
            }
        } else {
            swatchIndex = 0;
            groupIndex = 0;
        }
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
