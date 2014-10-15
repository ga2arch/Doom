//
//  WadLoader.cpp
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include "WadLoader.h"
#include <assert.h>
#include <string.h>


template <typename T>
auto WadLoader::load_lump(fstream& wad_file, vector<T>& v) -> void {
    
    T t;
    wad_file.read(reinterpret_cast<char *>(&t), sizeof t);
    v.push_back(t);
}

template <>
auto WadLoader::load_lump<Blockmap>(fstream& wad_file, vector<Blockmap>& v) -> void {
    Blockmap bm;
    int filepos = static_cast<int>(wad_file.tellg());
    
    wad_file.read(reinterpret_cast<char *>(&bm.header), sizeof bm.header);
    
    auto num_offsets = bm.header.col_num * bm.header.row_num;
    auto offsets = unique_ptr<uint16_t[]>(new uint16_t[num_offsets]);
    
    wad_file.read(reinterpret_cast<char *>(offsets.get()), sizeof(uint16_t)*num_offsets);
    
    for (int i=0; i<num_offsets; i++) {
        Block block;
        int16_t linedef;
        bool inblock (true);
        
        wad_file.seekg(filepos+offsets[i]*sizeof(uint16_t), wad_file.beg);
        
        while (inblock) {
            wad_file.read(reinterpret_cast<char *>(&linedef), sizeof(linedef));
            block.linedefs.push_back(linedef);

            if (linedef == -1)
                inblock = false;
        }
        
        bm.blocks.push_back(block);
    }
    
    v.push_back(bm);
}

template <>
auto WadLoader::load_lump<Sprite>(fstream& wad_file, vector<Sprite>& v) -> void {
    Sprite s;
    WadLump lump;
    
    cout << "Sprite" << endl;
    wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
    
    
    wad_file.read(reinterpret_cast<char *>(&s), sizeof s);
    auto offsets = unique_ptr<long[]>(new long[s.width]);
    
    wad_file.read(reinterpret_cast<char *>(offsets.get()), sizeof(uint16_t)*s.width);
    
    cout << s.heigth << endl;
}

auto WadLoader::load(fstream& wad_file) -> void {
    for (int i=0; i < wad.header.numlumps; i++) {
        
        WadLump lump;
        char* type;
        wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
        
        auto old = wad_file.tellg();
        wad_file.seekg(lump.filepos, wad_file.beg);
        
        type = (char *)"Things";
        if (!strncasecmp(type, lump.name, strlen(type))) {
            load_lump(wad_file, wad.things);
        }
        
        type = (char *)"Vertexes";
        if (!strncasecmp(type, lump.name, strlen(type))) {
            load_lump(wad_file, wad.vertexes);
        }
        
        type = (char *)"Ssectors";
        if (!strncasecmp(type, lump.name, strlen(type))) {
            load_lump(wad_file, wad.sectors);
        }
        
        type = (char *)"Nodes";
        if (!strncasecmp(type, lump.name, strlen(type))) {
            load_lump(wad_file, wad.nodes);
        }
        
        type = (char *)"Blockmap";
        if (!strncasecmp(type, lump.name, strlen(type))) {
            load_lump(wad_file, wad.blockmaps);
        }
        
        wad_file.seekg(old, wad_file.beg);
    }
    
}

auto WadLoader::load_file(const string& filename) -> void {
    WadHeader header;
    fstream wad_file(filename, fstream::in | fstream::binary);
    
    // Load header
    wad_file.read(reinterpret_cast<char*>(&header), sizeof(header));
    wad_file.seekg(header.infotableops, wad_file.beg);
    
    wad.header = header;
 
    load(wad_file);
    
    wad_file.close();
    
#ifdef DEBUG
    for (auto& e: wad.nodes) {
        //cout << e.blocks[0].linedefs[1]  << "\t" << endl;
        cout << e.node_ssector_num_left << endl;
        //printf("%.*s\n", 8, e.ceiling_tex);
    }
#endif
}