//
//  ofxASE.cpp
//  ofxASE
//
//  Created by James Hovet on 6/21/19.
//

#include "ofxASE.h"

ofxASE::ofxASE(){}

ofxASE::ofxASE(std::filesystem::path& filepath){
    load(filepath);
}

bool ofxASE::load(const std::filesystem::path& filepath){
    ofBuffer buffer = ofBufferFromFile(filepath);
    
    if(buffer.size() == 0){
        string absoluteFilePath = ofFilePath::getAbsolutePath(filepath, true);
        ofLogError("ofxASE") << "Couldn't load ASE file at: \"" << absoluteFilePath << "\"";
        return false;
    }
    
    char* buf = buffer.getData();
    
    if(buf[0] != 'A' || buf[1] != 'S' || buf[2] != 'E' || buf[3] != 'F'){
        ofLogError("ofxASE") << filepath.generic_string() << " is not a valid ASE file.";
        return false;
    }
    
    bool didLoadWithoutError = true;
    int head = 12;
    
    while(buf[head] == '\xc0' && buf[head + 1] == '\x01'){ // All group entries begin with 0xC001
        NamedColorGroup namedColorGroup;
        
        //read group name
        uint32_t nameByteLength = readBigEndian32(&buf[head + 2]);
        namedColorGroup.name = readBigEndian16String(&buf[head + 8], nameByteLength);

        head += 6 + (nameByteLength);
        
        //read each color block
        while (buf[head + 1] == '\x01') { // All color entries begin with 0x0001
            NamedColor namedColor;
            
            uint32_t colorBlockByteLength = readBigEndian32(&buf[head + 2]);
            uint16_t colorNameLength = readBigEndian16(&buf[head + 6]);
            namedColor.name = readBigEndian16String(&buf[head + 8], colorNameLength);
            
            int colorHead = head + 8 + (colorNameLength * 2);
            switch (buf[colorHead]){
                case 'R': //RGB
                    namedColor.color = readRGB(&buf[colorHead + 4]);
                    break;
                case 'C': //CMYK
                    namedColor.color = readCMYK(&buf[colorHead + 4]);
                    break;
                case 'L': //LAB
                    ofLogError() << "The LAB color space is not supported";
                    didLoadWithoutError = false;
                    break;
                case 'G': //Greyscale
                    namedColor.color = ofColor(readBigEndianFloat32(&buf[colorHead + 4]) * 256);
                    break;
            }
            
            namedColorGroup.namedColors.push_back(namedColor);
            allColors.push_back(namedColor);
            
            head += 6 + (colorBlockByteLength);
        }
        namedColorGroups.push_back(namedColorGroup);
        
        head += 6;
    }
    
    return didLoadWithoutError;
}

void ofxASE::clear(){
    namedColorGroups.clear();
    allColors.clear();
}

//-Utils--------------------------------------------------------
uint32_t ofxASE::readBigEndian32(char * start){
    uint32_t res;
    memcpy(&res, start, sizeof(uint32_t));
    
    //swap endianness on little endian systems
    #ifdef TARGET_LITTLE_ENDIAN
    return (((res & 0x000000FF) << 24) |
            ((res & 0x0000FF00) <<  8) |
            ((res & 0x00FF0000) >>  8) |
            ((res & 0xFF000000) >> 24));
    #endif
    
    return res;
}

Float32 ofxASE::readBigEndianFloat32(char * start){
    uint32_t bytes = readBigEndian32(start);
    Float32 res = *((Float32 *)&bytes);
    return res;
}

uint16_t ofxASE::readBigEndian16(char * start){
    uint16_t res;
    memcpy(&res, start, sizeof(uint16_t));
    
    //swap endianness on little endian systems
    #ifdef TARGET_LITTLE_ENDIAN
    return (((res & 0x00FF) << 8) |
            ((res & 0xFF00) >> 8));
    
    #endif
    
    return res;
}

ofColor ofxASE::readRGB(char * start){
    return ofColor(readBigEndianFloat32(start + 0) * 255,
                   readBigEndianFloat32(start + 4) * 255,
                   readBigEndianFloat32(start + 8)* 255);
}

ofColor ofxASE::readCMYK(char * start){
    Float32 C = readBigEndianFloat32(start + 0);
    Float32 M = readBigEndianFloat32(start + 4);
    Float32 Y = readBigEndianFloat32(start + 8);
    Float32 K = readBigEndianFloat32(start + 12);
    
    return ofColor(255 * (1.0 - C) * (1.0 - K),
                   255 * (1.0 - M) * (1.0 - K),
                   255 * (1.0 - Y) * (1.0 - K));
}

basic_string<char> ofxASE::readBigEndian16String(char * start, uint16_t length){
    char16_t wideString[length];
    memcpy(&wideString, start, length * sizeof(char16_t));
    
    #ifdef TARGET_LITTLE_ENDIAN // Switch endianness
    for(int i = 0; i<length; i++){
        char16_t c = wideString[i];
        wideString[i] = (((c & 0x00FF) << 8) |
                        ((c & 0xFF00) >> 8));
    }
    #endif
    
    static std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0xFFFF, std::little_endian>,char16_t> stringConversion;
    std::string converted = stringConversion.to_bytes(wideString);
    return converted;
}
