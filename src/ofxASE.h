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




class ofxASE {
private:
    
public:
    struct NamedColor {
        ofColor color;
        string name;
        
        operator ofColor() const {return color;}
    };
    
    struct NamedColorGroup {
        string name;
        std::vector<NamedColor> namedColors;
    };
    
    std::vector<NamedColorGroup> namedColorGroups;
    std::vector<NamedColor> allColors;

    bool load(const std::filesystem::path& filepath);
    void clear();
    
};

#endif /* ofxASE_hpp */
