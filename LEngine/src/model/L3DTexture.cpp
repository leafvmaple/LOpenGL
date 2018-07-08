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

bool L3DTexture::LoadTexture(const char* cszFileName)
{
    
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        _TextureBase TextureBase;
        
        bRetCode = CreateTexture(cszFileName, &TextureBase.nTexture);
        BOOL_ERROR_BREAK(bRetCode);
        
        m_vecTextures.push_back(TextureBase);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DTexture::LoadTexture(const char* pcszDirectory, BYTE*& pbyTexture)
{
    bool bResult = false;
    bool bRetCode = false;
    _TEXTURE* pTextureInfo = NULL;
    _MtlOption* pOption = NULL;
    char szTextureName[FILENAME_MAX];
    
    do
    {
        DWORD dwNumUsedTexture = 0;
        pbyTexture = LFileReader::Convert(pbyTexture, dwNumUsedTexture);
        
        for (DWORD dwTextIndex = 0; dwTextIndex < dwNumUsedTexture; dwTextIndex++)
        {
            pbyTexture = LFileReader::Convert(pbyTexture, pTextureInfo);
            
            sprintf(szTextureName, "%s%s", pcszDirectory, pTextureInfo->szTextureFileName);
            
            _TextureBase TextureBase;
            
            bRetCode = CreateTexture(szTextureName, &TextureBase.nTexture);
            BOOL_ERROR_BREAK(bRetCode);
            
            for (DWORD j = 0; j < pTextureInfo->dwTextureOptionCount; j++)
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
                        
                        pOption->pData = pDataReadIn;
                        break;
                    }
                    case OPTION_TEXTURE_MAPMETHOD:
                    {
                        _TextureMap* pDataReadIn = new _TextureMap;
                        pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                        pOption->pData = pDataReadIn;
                        break;
                    }
                    case OPTION_TEXTURE_TRANSFROM:
                    {
                        _TextureTf* pDataReadIn = new _TextureTf;
                        pbyTexture = LFileReader::Copy(pbyTexture, pDataReadIn);
                        
                        pOption->pData = pDataReadIn;
                        break;
                    }
                }
                TextureBase.vecTextureOptions.push_back(Option);
            }
            m_vecTextures.push_back(TextureBase);
        }
        
        bResult = true;
        
    } while (0);
    
    return bResult;
}

bool L3DTexture::UpdateTexture()
{
    for (int i = 0; i < m_vecTextures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_vecTextures[i].nTexture);
    }
    return true;
}

bool L3DTexture::CreateTexture(const char* cszFileName, DWORD* pTextureID)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        glGenTextures(1, pTextureID);
        glBindTexture(GL_TEXTURE_2D, *pTextureID);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_set_flip_vertically_on_load(true);
        
        int nWidth = 0;
        int nHeight = 0;
        int nChannels = 0;
        BYTE* pTexture = stbi_load(cszFileName, &nWidth, &nHeight, &nChannels, 0);
        BOOL_ERROR_BREAK(pTexture)
        
        glTexImage2D(GL_TEXTURE_2D,
                     0, GL_RGB, nWidth, nHeight,
                     0, GL_RGB, GL_UNSIGNED_BYTE,
                     pTexture);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(pTexture);
        
        bResult = true;
    } while (0);
    
    return bResult;
}
