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
    bool AttachObject(ILModel* pAction);

private:
    L3DWINDOWPARAM m_WindowParam;
    
    bool m_bActive;
    GLFWwindow* m_pWindow;

    LLIST<ILModel*> m_ModelList;
};

#endif /* LEngine_h */
