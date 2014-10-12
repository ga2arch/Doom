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
    Wad wad;

    fstream wad_file(filename, fstream::in | fstream::binary);
    
    wad_file.read(reinterpret_cast<char*>(&header.identification), sizeof(header.identification)-1);
    header.identification[4] = '\0';

    wad_file.read(reinterpret_cast<char*>(&header.numlumps), sizeof header.numlumps);
    wad_file.read(reinterpret_cast<char*>(&header.infotableops), sizeof header.infotableops);

    cout << sizeof(header.infotableops) << endl;
    
    vector<WadLump> lumps;
    wad_file.seekg(header.infotableops, wad_file.beg);
    
    for (int i=0; i < header.numlumps; i++) {
        WadLump lump;

        wad_file.read(reinterpret_cast<char *>(&lump.filepos), sizeof lump.filepos);
        wad_file.read(reinterpret_cast<char *>(&lump.size), sizeof lump.size);
        wad_file.read(reinterpret_cast<char *>(&lump.name), sizeof(lump.name)-1);
        lump.name[8] = '\0';
        
        lumps.push_back(lump);
    }
    
    for (auto& e: lumps) {
        cout << e.name << endl;
    }
    
    wad.header = header;
    wad.lumps  = lumps;
    
    wad_file.close();
    
}