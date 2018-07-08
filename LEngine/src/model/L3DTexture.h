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

enum OPTION_TEXTURE
{
    OPTION_TEXTURE_OPERATION = 1000,
    OPTION_TEXTURE_MAPMETHOD = 1001,
    OPTION_TEXTURE_TRANSFROM = 1002,
    OPTION_TEXTURE_ANIMATION = 1003,
    OPTION_TEXTURE_OPERATIONEX = 1004,
};

class L3DTexture
{
private:
    struct _TEXTURE
    {
        float fAmount;
        char  szTextureType[FILENAME_MAX];
        char  szTextureFileName[FILENAME_MAX];
        DWORD dwTextureOptionCount;
    };
    
    struct _MtlOption
    {
        DWORD Type;
        void* pData;
    };
    
    struct _MtlTextureOp
    {
        DWORD ColorOp;
        DWORD ColorArg1;
        DWORD ColorArg2;
        DWORD AlphaOp;
        DWORD AlphaArg1;
        DWORD AlphaArg2;
        DWORD TFactor;
        
        DWORD BakColorOp;
        DWORD BakColorArg1;
        DWORD BakColorArg2;
        DWORD BakAlphaOp;
        DWORD BakAlphaArg1;
        DWORD BakAlphaArg2;
        DWORD BakTFactor;
    };
    
    struct _TextureOpEx
    {
        DWORD ColorOp;
        DWORD ColorArg1;
        DWORD ColorArg2;
        DWORD ColorArg0;
        DWORD Result;
        DWORD AlphaOp;
        DWORD AlphaArg1;
        DWORD AlphaArg2;
        DWORD AlphaArg0;
        DWORD AlphaResult;
        DWORD TFactor;
        DWORD Constant;
        
        DWORD BakColorOp;
        DWORD BakColorArg1;
        DWORD BakColorArg2;
        DWORD BakColorArg0;
        DWORD BakResult;
        DWORD BakAlphaOp;
        DWORD BakAlphaArg1;
        DWORD BakAlphaArg2;
        DWORD BakAlphaArg0;
        DWORD BakTFactor;
        DWORD BakConstant;
    };
    
    struct _TextureMap
    {
        DWORD TextureMap;
        DWORD BakTextureMap;
    };
    
    struct _TextureTf
    {
        GLVec3 Scaling;
        GLVec3 Rotation;
        GLVec3 Position;
        GLVec3 Speed_Scaling;
        GLVec3 Speed_Rotation;
        GLVec3 Speed_Position;
    };
    
public:
    struct _TextureBase
    {
        DWORD nTexture;
        std::vector<_MtlOption> vecTextureOptions;
    };
    
public:
    L3DTexture();
    ~L3DTexture();
    
    bool Init();
    void Uninit();
    
    bool LoadTexture(const char* cszFileName);
    bool LoadTexture(const char* pcszDirectory, BYTE*& pbyTexture);
    
    bool UpdateTexture();
    
private:
    bool CreateTexture(const char* cszFileName, DWORD* pTextureID);
    
private:
    std::vector<_TextureBase> m_vecTextures;
};

#endif /* L3DTexture_h */
