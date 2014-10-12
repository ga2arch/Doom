//
//  WadLoader.h
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

#pragma pack(push, 1)

struct WadHeader {
    char identification[4];
    int numlumps;
    int infotableops;
};

#pragma pack(pop)

#pragma pack(push, 1)

struct WadLump {
    int filepos;
    int size;
    char name[8];
};

#pragma pack(pop)

#pragma pack(push, 1)

struct WadDirectory {
    
};

#pragma pack(pop)


struct WadFile {
    WadHeader header;
};

class WadLoader {
    
public:
    auto load_file(const string& filename) -> void;
    
    
private:
    WadFile wad;
};