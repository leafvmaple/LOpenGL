//
//  LClient.cpp
//  LOpenGL
//
//  Created by LeafMaple on 2018/06/19.
//  Copyright © 2018 LeafMaple. All rights reserved.
//
#ifdef WIN32
#include <windows.h>
#endif

#include "LClient.h"
#include "LInterface.h"
#include "LAssert.h"
#include "object/LObjectMgr.h"
#include "object/LCharacter.h"

LClient::LClient()
: m_fLastTime(0.0f)
{
    
}

LClient::~LClient()
{
    Uninit();
}

bool LClient::Init()
{
    bool bResult = false;
    bool bRetCode = false;
    L3DWINDOWPARAM WindowParam;
    
    do
    {
        WindowParam.Width = 800;
        WindowParam.Height = 600;
        WindowParam.lpszClassName = "LOpenGL";
        WindowParam.lpszWindowName = "L3D LOpenGL Engine";
        
        m_pEngine = IL3DEngine::Instance();
        BOOL_ERROR_BREAK(m_pEngine);

        bRetCode = m_pEngine->Init(WindowParam);
        BOOL_ERROR_BREAK(bRetCode);

        m_pObjectMgr = new LObjectMgr;
        BOOL_ERROR_BREAK(m_pObjectMgr);

        LCharacter *pCharacter = m_pObjectMgr->CreateModel<LCharacter>();
        BOOL_ERROR_BREAK(pCharacter);

        bResult = true;
    } while(0);
    
    return bResult;
}

bool LClient::Update()
{
    bool bResult = false;
    bool bRetCode = false;
    float fCurTime = 0;
    float fDeltaTime = 0;
    
    do
    {
        BOOL_ERROR_BREAK(m_pEngine);

#ifdef WIN32
        fCurTime = (float)timeGetTime();
        fDeltaTime = (fCurTime - m_fLastTime) * 0.001f;
#endif  
        bRetCode = m_pEngine->Update(fDeltaTime);
        BOOL_ERROR_BREAK(bRetCode);
        
        m_fLastTime = fCurTime;
        
        bResult = true;
    } while (0);
    
    return bResult;
}

void LClient::Uninit()
{
    if (m_pEngine)
    {
        m_pEngine->Uninit();
        m_pEngine = nullptr;
    }
}

bool LClient::IsActive()
{
    return m_pEngine && m_pEngine->IsActive();
}

int main()
{
    bool bRetCode = false;
    LClient Client;
    
    do
    {

        bRetCode = Client.Init();
        BOOL_ERROR_BREAK(bRetCode);
        
        while (Client.IsActive())
        {
            bRetCode = Client.Update();
            BOOL_ERROR_BREAK(bRetCode);
        }
        
    } while (0);

    Client.Uninit();
    
    return 0;
}
