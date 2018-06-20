//
//  TestPriv.hpp
//  Test
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

/* The classes below are not exported */
#pragma GCC visibility push(hidden)

class TestPriv
{
    public:
    void HelloWorldPriv(const char *);
};

#pragma GCC visibility pop
