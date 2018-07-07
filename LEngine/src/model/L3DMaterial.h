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

class L3DSubsetMaterial
{
public:
    L3DSubsetMaterial();
    
public:
    bool LoadLSubsetMaterial(const char* pcszDirectory, BYTE*& pbyMaterial);
    bool LoadOption(BYTE*& pbyMaterial);
    
    bool UpdateSubsetMaterial();
    
private:
    L3DTexture* m_p3DTexture;
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
