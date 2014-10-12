//
//  WadLoader.h
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

#include "Lumps.h"

using namespace std;

#pragma pack(push, 1)
struct WadHeader {
    char identification[4];
    int numlumps;
    int infotableops;
};

struct WadLump {
    int filepos;
    int size;
    char name[8];
};
#pragma pack(pop)

struct Wad {
    WadHeader header;
    vector<WadLump> lumps;
    vector<Vertex> vertexes;
    vector<Thing>  things;
};

class WadLoader {
    
public:
    auto load_file(const string& filename) -> void;
    
    
private:
    Wad wad;
    
    auto load_header() -> void;
};