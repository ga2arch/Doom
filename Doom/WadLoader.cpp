//
//  WadLoader.cpp
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "WadLoader.h"

template <typename T>
auto WadLoader::load_struct(fstream& wad_file, const char* type, vector<T>& v) -> void {
    WadLump lump;
    wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
    
    if (!strncmp(type, lump.name, strlen(type))) {
        T s;
        auto old = wad_file.tellg();
        
        wad_file.seekg(lump.filepos, wad_file.beg);
        wad_file.read(reinterpret_cast<char *>(&s), sizeof s);
        wad_file.seekg(old, wad_file.beg);
        
        v.push_back(s);
    }
}

auto WadLoader::load_file(const string& filename) -> void {
    WadHeader header;
    fstream wad_file(filename, fstream::in | fstream::binary);
    
    // Load header
    wad_file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Load lumps
    vector<Vertex>  vertexes;
    vector<Thing>   things;
    
    wad_file.seekg(header.infotableops, wad_file.beg);
    
    for (int i=0; i < header.numlumps; i++) {
        load_struct(wad_file, "THINGS", things);
        load_struct(wad_file, "VERTEXES", vertexes);
    }
    
    for (auto& e: vertexes) {
        cout << e.x << "\t" << e.y << endl;
    }
    
    wad.header = header;
    wad.vertexes = vertexes;
    wad.things   = things;
    
    wad_file.close();
    
}