//
//  LInterface.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include "LInterface.h"
#include "LEngine.h"
#include "LAssert.h"
#include "model/L3DModel.h"

IL3DEngine* IL3DEngine::m_pInstance = nullptr;

IL3DEngine* IL3DEngine::Instance()
{
    if (!m_pInstance)
        m_pInstance = new L3DEngine;
    return m_pInstance;
}

bool ILModel::Create(IL3DEngine* pIEngine,
                     const void* pModelVerteices,
                     GLsizeiptr nVerteicesCount,
                     const void* pwModelIndices,
                     GLsizeiptr nIndicesCount,
                     const char *pVertexPath,
                     const char *pFragmentPath,
                     ILModel** ppModel)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        BOOL_ERROR_BREAK(pIEngine);

        L3DModel* p3DModel = new L3DModel;
        BOOL_ERROR_BREAK(p3DModel);

        L3DEngine* pEngine = dynamic_cast<L3DEngine*>(pIEngine);
        BOOL_ERROR_BREAK(pEngine);

        bRetCode = p3DModel->Init(pModelVerteices,
                                  nVerteicesCount,
                                  pwModelIndices,
                                  nIndicesCount,
                                  pVertexPath,
                                  pFragmentPath);
        BOOL_ERROR_BREAK(bRetCode);

        pEngine->AttachObject(p3DModel);
        *ppModel = p3DModel;

        bResult = true;
    } while (0);

    return bResult;
}
