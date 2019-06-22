//
//  ofxASE.cpp
//  ofxASE
//
//  Created by James Hovet on 6/21/19.
//

#include "ofxASE.h"

uint32_t readBigEndian32(char * start){
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

uint16_t readBigEndian16(char * start){
    uint16_t res;
    memcpy(&res, start, sizeof(uint16_t));
    
    //swap endianness on little endian systems
    #ifdef TARGET_LITTLE_ENDIAN
    return (((res & 0x00FF) << 8) |
            ((res & 0xFF00) >> 8));
    
    #endif
    
    return res;
}


/// Load an ASE file into the ofxASE instance
bool ofxASE::load(const std::filesystem::path& filepath){
    ofBuffer buffer = ofBufferFromFile(filepath);
    
    if(!buffer.size()){
        string absoluteFilePath = ofFilePath::getAbsolutePath(filepath, true);
        ofLogError("ofxASE") << "Couldn't load ASE file at: \"" << absoluteFilePath << "\"";
        return false;
    }
    
    char* buf = buffer.getData();
    
    if(buf[0] != 'A' || buf[1] != 'S' || buf[2] != 'E' || buf[3] != 'F'){
        ofLogError("ofxASE") << filepath.generic_string() << " is not a valid ASE file.";
        return false;
    }
    
    int head = 12;
    
    while(buf[head] == '\xc0' && buf[head + 1] == '\x01'){
        SwatchGroup swatchGroup;
        
        //read group name
        uint32_t nameByteLength = readBigEndian32(&buf[head + 2]);
        swatchGroup.name = string(&buf[head + 8], nameByteLength);

        head += 6 + (nameByteLength);
        
        //read each color block
        while (buf[head + 1] == '\x01') {
            Swatch swatch;
            
            uint32_t colorBlockByteLength = readBigEndian32(&buf[head + 2]);
            uint16_t colorNameLength = readBigEndian16(&buf[head + 6]);
            string colorName = string(&buf[head + 8], colorNameLength * 2);
            
            
            
            swatch.name = colorName;
            
            allSwatches.push_back(swatch);
            swatchGroup.swatches.push_back(swatch);
            
            head += 6 + (colorBlockByteLength);
        }
        
        head += 6;
        
        swatchGroups.push_back(swatchGroup);
    }
    
    
//    for(auto swatchGroup : swatchGroups){
//        ofLogNotice() << swatchGroup.name;
//        for(auto swatch : swatchGroup.swatches){
//            ofLogNotice() << "|" << swatch.name;
//        }
//    }

}

//TODO: Actually import the colors
//TODO: Look into the trailing ones on some of these...
//TODO: Create the interface
