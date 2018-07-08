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
#include <algorithm>

L3DTexture::L3DTexture()
: m_nTexture(0)
{
    Init();
}

L3DTexture::~L3DTexture()
{
    Uninit();
}

bool L3DTexture::Init()
{
    return false;
}

void L3DTexture::Uninit()
{

}

bool L3DTexture::LoadTexture(const char* cszFileName)
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

        int nWidth = 0;
        int nHeight = 0;
        int nChannels = 0;
        GLubyte* pTexture = stbi_load(cszFileName, &nWidth, &nHeight, &nChannels, 0);
        BOOL_ERROR_BREAK(pTexture);
        
        GLuint uColorType = (nChannels == 3) ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D,
                     0, GL_RGB, nWidth, nHeight,
                     0, uColorType, GL_UNSIGNED_BYTE,
                     pTexture);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(pTexture);

        bResult = true;

        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DTexture::LoadTexture(const char* cszFileName, _TEXTURE* pTextureInfo, GLubyte*& pbyTexture)
{
    bool bResult = false;
    bool bRetCode = false;

    do
    {
        bRetCode = LoadTexture(cszFileName);
        BOOL_ERROR_BREAK(bRetCode);
            
        for (GLuint j = 0; j < pTextureInfo->dwTextureOptionCount; j++)
        {
            _MtlOption Option;
            pbyTexture = LFileReader::Convert(pbyTexture, Option.Type);
                
            switch(Option.Type)
            {
                case OPTION_TEXTURE_OPERATION:
                {
                    _MtlTextureOp* pDataReadIn = new _MtlTextureOp;
                    pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                    Option.pData = pDataReadIn;
                    break;
                }
                case OPTION_TEXTURE_OPERATIONEX:
                {
                    _TextureOpEx* pDataReadIn = new _TextureOpEx;
                    pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                    Option.pData = pDataReadIn;
                    break;
                }
                case OPTION_TEXTURE_MAPMETHOD:
                {
                    _TextureMap* pDataReadIn = new _TextureMap;
                    pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                    Option.pData = pDataReadIn;
                    break;
                }
                case OPTION_TEXTURE_TRANSFROM:
                {
                    _TextureTf* pDataReadIn = new _TextureTf;
                    pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                    Option.pData = pDataReadIn;
                    break;
                }
            }
            m_vecTextureOptions.push_back(Option);
        }

        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DTexture::UpdateTexture(GLuint uIndex)
{
    glActiveTexture(GL_TEXTURE0 + uIndex);
    glBindTexture(GL_TEXTURE_2D, m_nTexture);
    return true;
}

GLuint L3DTexture::GetTextureID() const
{
    return m_nTexture;
}
