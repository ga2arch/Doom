//
//  WadLoader.h
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "Lumps.h"

using namespace std;

#pragma pack(push, 1)
struct WadHeader {
    char identification[4];
    int32_t numlumps;
    int32_t infotableops;
};

struct WadLump {
    int32_t filepos;
    int32_t size;
    char name[8];
};
#pragma pack(pop)

struct Wad {
    WadHeader header;

    vector<Thing>    things;
    vector<Vertex>   vertexes;
    vector<Sector>   sectors;
    vector<Blockmap> blockmaps;
    vector<Node>     nodes;
    vector<Sprite>   sprites;
    vector<Flat>     flats;
    Playpal          playpal;
};

class WadLoader {
    
public:
    auto load_file(const string& filename) -> void;
    
private:
    Wad wad;

    template <typename T>
    auto load_lump(fstream& wad_file, T& v) -> void;
    
    template <typename T>
    auto load_lumps(fstream& wad_file, vector<T>& v) -> void;
    
    auto load(fstream& wad_file) -> void;
    auto check_type(const char* type, char name[8]) -> bool;
};