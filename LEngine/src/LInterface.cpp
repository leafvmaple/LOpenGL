//
//  LInterface.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include "LInterface.h"
#include "LEngine.h"

IL3DEngine* IL3DEngine::m_pInstance = nullptr;

IL3DEngine* IL3DEngine::Instance()
{
    if (!m_pInstance)
        m_pInstance = new L3DEngine;
    return m_pInstance;
}
