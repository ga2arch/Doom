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

auto WadLoader::load_struct(fstream& wad_file, vector<Blockmap>& v) -> void {
    WadLump lump;
    wad_file.read(reinterpret_cast<char *>(&lump), sizeof lump);
    
    if (!strncmp("BLOCKMAP", lump.name, strlen("BLOCKMAP"))) {
        Blockmap bm;
        
        auto old = wad_file.tellg();

        wad_file.seekg(lump.filepos, wad_file.beg);
        wad_file.read(reinterpret_cast<char *>(&bm.header), sizeof bm.header);
        
        auto num_offsets = bm.header.col_num * bm.header.row_num;
        auto offsets = unique_ptr<uint16_t[]>(new uint16_t[num_offsets]);
        
        wad_file.read(reinterpret_cast<char *>(offsets.get()), sizeof(uint16_t)*num_offsets);
        
        for (int i=0; i<num_offsets; i++) {
            Block block;
            bool inblock = true;

            wad_file.seekg(lump.filepos+offsets[i]*sizeof(int16_t), wad_file.beg);
            wad_file.read(reinterpret_cast<char *>(&start), sizeof(start));
           
            while (inblock) {
                int16_t linedef;
                wad_file.read(reinterpret_cast<char *>(&linedef), sizeof(linedef));
                block.linedefs.push_back(linedef);

                if (linedef == -1)
                    inblock = false;
            }

            bm.blocks.push_back(block);
        }
        
        wad_file.seekg(old, wad_file.beg);
        v.push_back(bm);
    }
}

auto WadLoader::load_file(const string& filename) -> void {
    WadHeader header;
    fstream wad_file(filename, fstream::in | fstream::binary);
    
    // Load header
    wad_file.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Load lumps
    vector<Vertex> vertexes;
    vector<Thing> things;
    vector<Sector> sectors;
    vector<Blockmap> blockmaps;
    
    wad_file.seekg(header.infotableops, wad_file.beg);
    
    for (int i=0; i < header.numlumps; i++) {
        load_struct(wad_file, "THINGS", things);
        load_struct(wad_file, "VERTEXES", vertexes);
        load_struct(wad_file, blockmaps);
    }
    
    for (auto& e: blockmaps) {
        cout << e.blocks[0].linedefs[0]  << "\t" << endl;
        //printf("%.*s\n", 8, e.ceiling_tex);
    }
    
    wad.header = header;
    wad.vertexes = vertexes;
    wad.things   = things;
    wad.blockmaps = blockmaps;
    
    wad_file.close();
    
}