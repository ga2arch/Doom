//
//  main.cpp
//  Doom
//
//  Created by Gabriele on 12/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#include <iostream>

#include "WadLoader.h"

int main(int argc, const char * argv[]) {
    WadLoader loader;
    
    loader.load_file("doom.wad");
}

