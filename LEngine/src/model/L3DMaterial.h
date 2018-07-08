//
//  L3DMaterial.hpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef _L3DMaterial_H_
#define _L3DMaterial_H_

#include <stdio.h>
#include "LDefine.h"

#define MAX_SUBSET_COUNT 32
#define NORMALIZE_MAT_POWER(a) { if (a > 100.0f || a <= 0.0f) a = 15.0f; }
#define MATERIAL_OPTION_VERSION_2        (1 << 18)

class L3DTexture;

typedef struct L3DMATERIAL {
    LCOLOR_RGBA_FLOAT Diffuse;
    LCOLOR_RGBA_FLOAT Ambient;
    LCOLOR_RGBA_FLOAT Specular;
    LCOLOR_RGBA_FLOAT Emissive;
    float Power;
} L3DMATERIAL;

class L3DSubsetMaterial
{
public:
    L3DSubsetMaterial();
    ~L3DSubsetMaterial();
    
public:
    bool LoadLSubsetMaterial(const char* pcszDirectory, BYTE*& pbyMaterial);
    bool LoadOption(BYTE*& pbyMaterial);
    
    bool UpdateSubsetMaterial();
    
private:
    enum MATERIAL_OPTION
    {
        MATERIAL_OPTION_EMAP = (1 << 20),
        MATERIAL_OPTION_INCLUDEALLDEFAULTCOLORCAST = (1 << 21),
        MATERIAL_OPTION_SORTASSFX = (1<<22),
        MATERIAL_OPTION_DETAIL = (1<<23),
        MATERIAL_OPTION_TEXTUREBLEND = (1<<24),
        MATERIAL_OPTION_SETCOLOR = (1<<25),
    };
    
    const static int cNumID = 8;
    const static int cNumColorCast = 8;
    DWORD m_dwOption;
    L3DMATERIAL m_Material;
    L3DTexture* m_p3DTexture;
    
    LCOLOR_RGBA_FLOAT m_ColorCast[cNumColorCast];
    float            m_fSpecPower;
    float            m_fEmssPower;
};

class L3DMaterial
{
public:
    bool LoadLMaterial(const char* cszFileName);
    bool UpdateMaterial(DWORD dwSubMaterial);
    
private:
    DWORD m_dwNumMaterials;
    L3DSubsetMaterial* m_pMaterialSubset;
};

#endif /* _L3DMaterial_H_ */
