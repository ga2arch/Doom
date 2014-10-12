//
//  Lumps.h
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#pragma pack(push, 1)

struct Vertex {
    int16_t x;
    int16_t y;
};

struct Thing {
    int16_t x;
    int16_t y;
    int16_t angle;
    int16_t type;
    int16_t options;
};

#pragma pack(pop)
