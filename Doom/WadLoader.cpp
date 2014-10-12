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
    
    // Load header
    wad_file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Load lumps
    vector<WadLump> lumps;
    vector<Vertex>  vertexes;
    vector<Thing>   things;
    
    wad_file.seekg(header.infotableops, wad_file.beg);
    
    for (int i=0; i < header.numlumps; i++) {
        WadLump lump;

        wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
        lumps.push_back(lump);
        
        if (strncmp("VERTEXES", lump.name, 7) == 0) {
            Vertex v;
            auto old = wad_file.tellg();
            
            wad_file.seekg(lump.filepos, wad_file.beg);
            wad_file.read(reinterpret_cast<char *>(&v), sizeof v);
            wad_file.seekg(old, wad_file.beg);
            
            vertexes.push_back(v);
        }
        
        if (strncmp("THINGS", lump.name, 6) == 0) {
            Thing t;
            auto old = wad_file.tellg();
            
            wad_file.seekg(lump.filepos, wad_file.beg);
            wad_file.read(reinterpret_cast<char *>(&t), sizeof t);
            wad_file.seekg(old, wad_file.beg);
            
            things.push_back(t);
        }
    }
    
    for (auto& e: things) {
        cout << e.x << "\t" << e.y << endl;
    }
    
    wad.header = header;
    wad.lumps  = lumps;
    wad.vertexes = vertexes;
    wad.things   = things;
    
    wad_file.close();
    
}