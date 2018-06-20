//
//  LEngine.h
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef LEngine_h
#define LEngine_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LInterface.h"

class L3DEngine : public IL3DEngine
{
public:
    L3DEngine();
    virtual ~L3DEngine();
    
    virtual bool Init(L3DWINDOWPARAM& WindowParam);
    virtual bool Uninit();
    
    virtual bool Update(float fDeltaTime);
    
    virtual bool IsActive();
    
private:
    L3DWINDOWPARAM m_WindowParam;
    
    bool m_bActive;
    GLFWwindow* m_pWindow;
};

#endif /* LEngine_h */
