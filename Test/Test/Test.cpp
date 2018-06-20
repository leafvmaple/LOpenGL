//
//  Test.cpp
//  Test
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <iostream>
#include "Test.hpp"
#include "TestPriv.hpp"

void Test::HelloWorld(const char * s)
{
    TestPriv *theObj = new TestPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void TestPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

