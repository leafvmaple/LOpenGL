//
//  LEngine.h
//  LEngine
//
//  Created by LeafMaple on 2018/06/20.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef LEngine_h
#define LEngine_h

#include "LInterface.h"

class L3DModel;
class L3DInput;
class L3DCamera;

class L3DEngine : public IL3DEngine
{
public:
    L3DEngine();
    virtual ~L3DEngine();
    
    virtual bool Init(L3DWINDOWPARAM& WindowParam);
    virtual void Uninit();
    
    virtual bool Update(float fDeltaTime);
    
    virtual bool IsActive();

public:
    bool AttachObject(L3DModel* pAction);

private:
    L3DWINDOWPARAM m_WindowParam;
    
    bool m_bActive;
    GLFWwindow* m_pWindow;

    L3DInput*  m_p3DInput;
    L3DCamera* m_p3DCamera;

    std::list<L3DModel*> m_ModelList;

private:
    bool UpdateInput(float fDeltaTime);
    bool UpdateCamera(float fDeltaTime);
};

#endif /* LEngine_h */
