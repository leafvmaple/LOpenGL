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

class L3DENGINE_CLASS IL3DEngine;
class LObjectMgr;

class LClient
{
public:
    LClient();
    ~LClient();
    
    bool Init();
    bool Update();
    void Uninit();

    bool IsActive();
    
private:
    IL3DEngine* m_pEngine;
    LObjectMgr* m_pObjectMgr;
    
    float m_fLastTime;
};


#endif /* LClient_h */
