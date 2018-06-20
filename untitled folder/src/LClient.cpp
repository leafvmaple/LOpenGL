//
//  LGLMain.cpp
//  LOpenGL
//
//  Created by LeafMaple on 2018/06/19.
//  Copyright © 2018 LeafMaple. All rights reserved.
//


#include "LClient.h"
#include "L3DInterface.h"
#include "LAssert.h"

LClient::LClient()
{
    
}

Lclient::~LClient()
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
        
        m_pEngine = new IL3DEngine(WindowParam);
    } while(0);
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
            hr = Client.Update();
            HRESULT_ERROR_BREAK(hr);
        }
        
    } while (0);
    
    Client.Uninit();
    
    return 0;
}
