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

using namespace std;

struct WadHeader {
    char identification[5];
    int numlumps;
    int infotableops;
};

struct WadLump {
    int filepos;
    int size;
    char name[9];
};

struct Wad {
    WadHeader header;
    vector<WadLump> lumps;
};

class WadLoader {
    
public:
    auto load_file(const string& filename) -> void;
    
    
private:
    Wad wad;
};