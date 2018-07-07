//
//  L3DTexture.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/05.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <memory.h>

#include "L3DTexture.h"
#include "stb/stb_image.h"
#include "io/LFileReader.h"

L3DTexture::L3DTexture()
: m_nTexture(0)
, n_nWidth(0)
, m_nHeight(0)
, m_nChannels(0)
{
    Init();
}

L3DTexture::~L3DTexture()
{
    Uninit();
}

bool L3DTexture::Init()
{
    m_vecTextures.clear();
    return true;
}

void L3DTexture::Uninit()
{
    m_vecTextures.clear();
}

bool L3DTexture::LoadLTexture(const char* cszFileName)
{
    
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        glGenTextures(1, &m_nTexture);
        glBindTexture(GL_TEXTURE_2D, m_nTexture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_set_flip_vertically_on_load(true);
        BYTE* pTexture = stbi_load(cszFileName, &n_nWidth, &m_nHeight, &m_nChannels, 0);
        BOOL_ERROR_BREAK(pTexture)
        
        glTexImage2D(GL_TEXTURE_2D,
                     0, GL_RGB, n_nWidth, m_nHeight,
                     0, GL_RGB, GL_UNSIGNED_BYTE,
                     pTexture);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(pTexture);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DTexture::UpdateTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_nTexture);
    return true;
}
