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

#define MAT_TEXTURETYPE_LENGTH 20
#define MAT_TEXTUREFILENAME_LENGTH 256

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
    friend class LTextureCreator;

    struct _MtlOption
    {
        GLuint Type;
        void* pData;
    };
    
    struct _MtlTextureOp
    {
        GLuint ColorOp;
        GLuint ColorArg1;
        GLuint ColorArg2;
        GLuint AlphaOp;
        GLuint AlphaArg1;
        GLuint AlphaArg2;
        GLuint TFactor;
        
        GLuint BakColorOp;
        GLuint BakColorArg1;
        GLuint BakColorArg2;
        GLuint BakAlphaOp;
        GLuint BakAlphaArg1;
        GLuint BakAlphaArg2;
        GLuint BakTFactor;
    };
    
    struct _TextureOpEx
    {
        GLuint ColorOp;
        GLuint ColorArg1;
        GLuint ColorArg2;
        GLuint ColorArg0;
        GLuint Result;
        GLuint AlphaOp;
        GLuint AlphaArg1;
        GLuint AlphaArg2;
        GLuint AlphaArg0;
        GLuint AlphaResult;
        GLuint TFactor;
        GLuint Constant;
        
        GLuint BakColorOp;
        GLuint BakColorArg1;
        GLuint BakColorArg2;
        GLuint BakColorArg0;
        GLuint BakResult;
        GLuint BakAlphaOp;
        GLuint BakAlphaArg1;
        GLuint BakAlphaArg2;
        GLuint BakAlphaArg0;
        GLuint BakTFactor;
        GLuint BakConstant;
    };
    
    struct _TextureMap
    {
        GLuint TextureMap;
        GLuint BakTextureMap;
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
    struct _TEXTURE
    {
        float fAmount;
        char  szTextureType[MAT_TEXTURETYPE_LENGTH];
        char  szTextureFileName[MAT_TEXTUREFILENAME_LENGTH];
        GLuint dwTextureOptionCount;
    };
    
public:
    L3DTexture();
    ~L3DTexture();
    
    bool Init();
    void Uninit();
    
    bool LoadTexture(const char* cszFileName);
    bool LoadTexture(const char* cszFileName, _TEXTURE* pTextureInfo, GLubyte*& pbyTexture);
    bool UpdateTexture(GLuint uIndex);
    
    GLuint GetTextureID() const;
    
private:
    GLuint m_nTexture;
    std::vector<_MtlOption> m_vecTextureOptions;
};

#endif /* L3DTexture_h */
