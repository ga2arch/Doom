//
//  Lumps.h
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#pragma pack(push, 1)

struct Thing {
    int16_t x;
    int16_t y;
    int16_t angle;
    int16_t type;
    int16_t flag;
};

struct Linedef {
    int16_t from;
    int16_t to;
    int16_t flags;
    int16_t types;
    int16_t tag;
    int16_t rigth_sidedef;
    int16_t left_sidedef;
};

struct Sidedef {
    int16_t x_offset;
    int16_t y_offset;
    char upper_text_name[8];
    char lower_text_name[8];
    char middle_text_name[8];
    int16_t sector;
};

struct Vertex {
    int16_t x;
    int16_t y;
};

struct Seg {
    int16_t start;
    int16_t end;
    int16_t angle;
    int16_t linedef;
    int16_t direction;
    int16_t offset;
};

struct Subsector {
    int16_t segs_num;
    int16_t segs_start;
};

struct Node {
    int32_t x;
    int32_t y;
    int32_t dx;
    int32_t dy;
    
    int16_t y_upper_bound_rigth;
    int16_t y_lower_bound_rigth;
    int16_t x_upper_bound_rigth;
    int16_t x_lower_bound_rigth;
    
    int16_t y_upper_bound_left;
    int16_t y_lower_bound_left;
    int16_t x_upper_bound_left;
    int16_t x_lower_bound_left;
    
    int16_t node_ssector_num_rigth;
    int16_t node_ssector_num_left;
};

struct Sector {
    int16_t floor_heigth;
    int16_t ceiling_heigth;
    char floor_tex[8];
    char ceiling_tex[8];
    int16_t ligthlevel;
    int16_t special_sector;
    int16_t tag;
};

struct Header {
    int16_t x;
    int16_t y;
    int16_t col_num;
    int16_t row_num;
};

struct Block {
    std::vector<int16_t> linedefs;
};

struct Blockmap {
    Header header;
    std::vector<Block> blocks;
};



#pragma pack(pop)
