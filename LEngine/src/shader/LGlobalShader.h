//
//  LGlobalShader.h
//  LEngine
//
//  Created by LeafMaple on 2018/07/10.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef LGlobalShader_h
#define LGlobalShader_h

class L3DShader;

class LGlobalShader
{
public:
    static L3DShader* Instance();
    
private:
    static L3DShader* m_pGlobalShader;
    
private:
    LGlobalShader();
    ~LGlobalShader();
};

#endif /* LGlobalShader_h */
