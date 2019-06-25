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
#include "ofFileUtils.h" //needed for ofBuffer
#include <codecvt> //converts UTF16 text encoding to UTF8, which has better support in openFrameworks


class ofxASE {
public:
    struct NamedColor {
        ofColor color;
        string name; /// utf8
        
        operator ofColor() const {return color;}
    };
    
    struct NamedColorGroup {
        string name; /// utf8
        std::vector<NamedColor> namedColors;
        
        inline const std::vector<NamedColor> getColors() const {return namedColors;}
    };
    
    ofxASE();
    /// Construct an ofxASE instance and load in a single .ase swatch file.
    ofxASE(std::filesystem::path& filepath);
    
    /// Load an ASE file into the ofxASE instance. Multiple files can be loaded into the same instance. Assuses target system uses IEEE 754 floating point values. Returns false if unsuccessful.
    bool load(const std::filesystem::path& filepath);
    /// Clear the ofxASE instance of all colors and color groups
    void clear();
    /// Return a std::vector of all color groups in this ofxASE instance
    std::vector<NamedColorGroup> getGroups() const {return namedColorGroups;}
    /// Return a std::vector of every color in this ofxASE instance
    std::vector<NamedColor> getAllColors() const {return allColors;}
    
private:
    
    std::vector<NamedColorGroup> namedColorGroups;
    std::vector<NamedColor> allColors;
    
    
    static uint32_t readBigEndian32(char * start);
    static Float32 readBigEndianFloat32(char * start);
    static uint16_t readBigEndian16(char * start);
    static ofColor readRGB(char * start);
    static ofColor readCMYK(char * start);
    static basic_string<char> readBigEndian16String(char * start, uint16_t length);
    
};

#endif /* ofxASE_hpp */
