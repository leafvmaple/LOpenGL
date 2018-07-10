//
//  LGloablShader.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/10.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include "LGlobalShader.h"
#include "L3DShader.h"

L3DShader* LGlobalShader::m_pGlobalShader = nullptr;

L3DShader* LGlobalShader::Instance()
{
    if (m_pGlobalShader == nullptr)
        m_pGlobalShader = new L3DShader;
    return m_pGlobalShader;
}
