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
auto WadLoader::load(fstream& wad_file, vector<T>& v) -> void {
    WadLump lump;
    wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
    auto old = wad_file.tellg();
    
    auto name = TypeName<T>::Get();

    if (!strncasecmp(name, lump.name, strlen(name))) {
        wad_file.seekg(lump.filepos, wad_file.beg);

        load_lump(wad_file, v);
        
        wad_file.seekg(old, wad_file.beg);
    }
    
}

template <typename T>
auto WadLoader::load_lump(fstream& wad_file, vector<T>& v) -> void {
    
    T t;
    wad_file.read(reinterpret_cast<char *>(&t), sizeof t);
    v.push_back(t);
}

template<>
auto WadLoader::load_lump<Blockmap>(fstream& wad_file, vector<Blockmap>& v) -> void {
    Blockmap bm;
    int filepos = static_cast<int>(wad_file.tellg());
    
    wad_file.read(reinterpret_cast<char *>(&bm.header), sizeof bm.header);
    
    auto num_offsets = bm.header.col_num * bm.header.row_num;
    auto offsets = unique_ptr<uint16_t[]>(new uint16_t[num_offsets]);
    
    wad_file.read(reinterpret_cast<char *>(offsets.get()), sizeof(uint16_t)*num_offsets);
    
    for (int i=0; i<num_offsets; i++) {
        Block block;
        bool inblock = true;
        
        wad_file.seekg(filepos+offsets[i]*sizeof(uint16_t), wad_file.beg);
        
        while (inblock) {
            int16_t linedef;
            wad_file.read(reinterpret_cast<char *>(&linedef), sizeof(linedef));
            block.linedefs.push_back(linedef);

            if (linedef == -1)
                inblock = false;
        }
        
        bm.blocks.push_back(block);
    }
    
    v.push_back(bm);
}

auto WadLoader::load_file(const string& filename) -> void {
    WadHeader header;
    fstream wad_file(filename, fstream::in | fstream::binary);
    
    // Load header
    wad_file.read(reinterpret_cast<char*>(&header), sizeof(header));

    wad_file.seekg(header.infotableops, wad_file.beg);
    
    for (int i=0; i < header.numlumps; i++) {
        load(wad_file, wad.things);
        load(wad_file, wad.vertexes);
        load(wad_file, wad.sectors);
        load(wad_file, wad.blockmaps);
        load(wad_file, wad.nodes);
    }
    
    wad_file.close();
    
#ifdef DEBUG
    for (auto& e: wad.sectors) {
        //cout << e.blocks[0].linedefs[1]  << "\t" << endl;
        cout << e.ceiling_heigth << endl;
        //printf("%.*s\n", 8, e.ceiling_tex);
    }
#endif
}