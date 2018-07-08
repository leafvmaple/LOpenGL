//
//  ILEngine.h
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef _LINTERFACE_H_
#define _LINTERFACE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LDefine.h"
#include "LExports.h"
#include "LAssert.h"
#include "LSTL.h"

typedef unsigned int GLCOLOR;

struct L3DWINDOWPARAM
{
    int x;
    int y;
    int Width;
    int Height;
    bool bWindow;
    const char* lpszClassName;
    const char* lpszWindowName;
};

class L3DENGINE_CLASS IL3DEngine
{
public:
    virtual ~IL3DEngine() {};
    
    virtual bool Init(L3DWINDOWPARAM& WindowParam) = 0;
    virtual void Uninit() = 0;
    
    virtual bool Update(float fDeltaTime) = 0;
    
    virtual bool IsActive() = 0;
    
    static IL3DEngine* Instance();
    
protected:
    IL3DEngine() {};
    
private:
    static IL3DEngine* m_pInstance;
};

class L3DENGINE_CLASS ILModel
{
public:
    ILModel() {};
    virtual ~ILModel() {};
    
    static bool Create(IL3DEngine* pIEngine, const char* cszFileName, ILModel** ppModel);
};

#endif /* LInterface_h */

