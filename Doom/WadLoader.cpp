//
//  WadLoader.cpp
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "WadLoader.h"

auto WadLoader::load_file(const string& filename) -> void {
    
    WadHeader header;
    WadLump lump;
    Wad wad;

    fstream wad_file(filename, fstream::in | fstream::binary);
    
    wad_file.read(reinterpret_cast<char *>(&header), sizeof(header));
    
    cout << header.numlumps << endl;
    
    auto length = header.numlumps * sizeof(lump);
    auto lumps = unique_ptr<WadLump[]>(new WadLump[length]);
    
    wad_file.seekg(header.infotableops, wad_file.beg);
    wad_file.read(reinterpret_cast<char *>(lumps.get()), length);
    
    vector<WadLump> vlumps(lumps.get(), lumps.get()+header.numlumps);
    
    wad.header = header;
    wad.lumps = vlumps;
    
    wad_file.close();
    
}