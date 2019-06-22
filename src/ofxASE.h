//
//  ofxASE.h
//  ofxASE
//
//  Created by James Hovet on 6/21/19.
//
/// Reads Adobe ASE files from Adobe Color (https://color.adobe.com) or other Adobe programs.

#ifndef ofxASE_hpp
#define ofxASE_hpp

#include "ofMain.h"
#include "ofFileUtils.h"
#include <stdio.h>

struct Swatch {
    ofColor color;
    string name;
};

struct SwatchGroup {
    string name;
    std::vector<Swatch> swatches;
};


class ofxASE {
public:
    std::vector<SwatchGroup> swatchGroups;
    std::vector<Swatch> allSwatches;

    bool load(const std::filesystem::path& filepath);
    
};

#endif /* ofxASE_hpp */
