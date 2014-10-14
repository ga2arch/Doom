//
//  Utils.h
//  Doom
//
//  Created by Gabriele on 15/10/14.
//  Copyright (c) 2014 Ga2 & co. All rights reserved.
//

#define ENABLE_TYPENAME(A, B) template<> struct TypeName<A> { static const char *Get() { return B; }};

template <typename T>
struct TypeName {
    static const char* Get() {
        return typeid(T).name();
    }
};
