//
//  WadLoader.cpp
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "WadLoader.h"

auto WadLoader::load_file(const string &filename) -> void {
    
    WadHeader header;
    fstream wad_file(filename, fstream::in | fstream::binary);
    
    wad_file.read(reinterpret_cast<char *>(&header), sizeof(header));
    
    cout << header.numlumps << endl;
}