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
#include <vector>
#include "LDefine.h"

#define MAX_SUBSET_COUNT 32
#define NORMALIZE_MAT_POWER(a) { if (a > 100.0f || a <= 0.0f) a = 15.0f; }
#define MATERIAL_OPTION_VERSION_2        (1 << 18)

class L3DTexture;
class L3DShader;
class L3DCamera;

class L3DSubsetMaterial
{
    friend class LMaterialCreator;

public:
    L3DSubsetMaterial();
    ~L3DSubsetMaterial();

public:
    bool LoadLSubsetMaterial(const char* pcszDirectory, GLubyte*& pbyMaterial);
    bool LoadOption(GLubyte*& pbyMaterial);
    
    bool UpdateSubsetMaterial();
    bool UpdatePosition(L3DCamera *p3DCamera);
    
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
    GLuint m_dwOption;
    L3DMATERIAL m_Material;
    L3DShader* m_p3DShader;
    std::vector<L3DTexture*> m_vecTexture;
    
    LCOLOR_RGBA_FLOAT m_ColorCast[cNumColorCast];
    float            m_fSpecPower;
    float            m_fEmssPower;
};

class L3DMaterial
{
public:
    bool LoadLMaterial(const char* cszFileName);
    bool UpdateMaterial(GLuint dwSubMaterial);
    bool UpdatePosition(L3DCamera* p3DCamera);
    
private:
    GLuint m_dwNumMaterials;
    L3DSubsetMaterial* m_pMaterialSubset;
};

#endif /* _L3DMaterial_H_ */
