//
//  LClient.h
//  LClient
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef LClient_h
#define LClient_h

#include "LAssert.h"
#include "LExports.h"

class IL3DEngine;

class LClient
{
public:
    LClient();
    ~LClient()
    
    bool Init();
    
private:
    IL3DEngine* m_pEngine;
};


#endif /* LClient_h */
