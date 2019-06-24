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
        string name; //utf8
        
        operator ofColor() const {return color;}
    };
    
    struct NamedColorGroup {
        string name;
        std::vector<NamedColor> namedColors;
        
        inline const std::vector<NamedColor> getColors() const {return namedColors;}
    };
    
    ofxASE();
    ofxASE(std::filesystem::path& filepath);
    
    bool load(const std::filesystem::path& filepath);
    void clear();
    std::vector<NamedColorGroup> getGroups() const {return namedColorGroups;}
    std::vector<NamedColor> getAllColors() const {return allColors;}
    
private:
    
    std::vector<NamedColorGroup> namedColorGroups;
    std::vector<NamedColor> allColors;
    
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0xFFFF, std::little_endian>,char16_t> stringConversion;
    
    //Utils
    uint32_t readBigEndian32(char * start);
    Float32 readBigEndianFloat32(char * start);
    uint16_t readBigEndian16(char * start);
    ofColor readRGB(char * start);
    ofColor readCMYK(char * start);
    basic_string<char> readBigEndian16String(char * start, uint16_t length);
    
};

#endif /* ofxASE_hpp */
