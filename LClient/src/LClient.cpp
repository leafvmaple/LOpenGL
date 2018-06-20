//
//  LGLMain.cpp
//  LOpenGL
//
//  Created by LeafMaple on 2018/06/19.
//  Copyright © 2018 LeafMaple. All rights reserved.
//


#include "LClient.h"
#include "LInterface.h"
#include "LAssert.h"
#include <time.h>

LClient::LClient()
: m_fLastTime(0.0f)
{
    
}

LClient::~LClient()
{
    
}

bool LClient::Init()
{
    L3DWINDOWPARAM WindowParam;
    
    do
    {
        WindowParam.Width = 800;
        WindowParam.Height = 600;
        WindowParam.lpszClassName = "LDirectX";
        WindowParam.lpszWindowName = "L3D DirectX9 Engine";
        
        m_pEngine = IL3DEngine::Instance();
        
        m_pEngine->Init(WindowParam);
    } while(0);
    
    return true;
}

bool LClient::Update()
{
    bool bResult = false;
    bool bRetCode = false;
    float fCurTime = 0;
    float fDeltaTime = 0;
    
    do {
        //fCurTime = (float)GetTickCount();
        //fDeltaTime = (fCurTime - m_fLastTime) * 0.001f;
        
        bRetCode = m_pEngine->Update(fDeltaTime);
        BOOL_ERROR_BREAK(bRetCode);
        
        m_fLastTime = fCurTime;
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool LClient::IsActive()
{
    return m_pEngine->IsActive();
}

int main()
{
    bool bRetCode = false;
    LClient Client;
    
    do {
        bRetCode = Client.Init();
        BOOL_ERROR_BREAK(bRetCode);
        
        while (Client.IsActive())
        {
            bRetCode = Client.Update();
            BOOL_ERROR_BREAK(bRetCode);
        }
        
    } while (0);
    
    return 0;
}
