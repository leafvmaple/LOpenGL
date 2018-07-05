//
//  L3DTexture.h
//  LEngine
//
//  Created by LeafMaple on 2018/07/05.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef L3DTexture_h
#define L3DTexture_h

#include "LInterface.h"

class L3DTexture
{
public:
    struct _TextureBase
    {
        unsigned char* pTexture;
    };
    
public:
    L3DTexture();
    ~L3DTexture();
    
    bool Init();
    void Uninit();
    
    bool LoadLTexture(const char* cszFileName);
    bool LoadLTexture(const char* pcszDirectory, BYTE*& pbyTexture);
    
    bool UpdateTexture();
    
private:
    unsigned int m_nTexture;
    
    int n_nWidth;
    int m_nHeight;
    int m_nChannels;
    
    std::vector<_TextureBase*> m_vecTextures;
};

#endif /* L3DTexture_h */
