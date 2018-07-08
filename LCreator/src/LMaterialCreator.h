#ifndef _LMATERIAL_CREATOR_H_
#define _LMATERIAL_CREATOR_H_

#include "LDefine.h"
#include "LTextureCreator.h"
#include <vector>

class LMaterialCreator
{
public:
    LMaterialCreator();
    ~LMaterialCreator();

    bool Init();
    bool Create(const char* cszFileName);

    bool SetMaterial(L3DMATERIAL* pMaterial);
    bool SetOption(GLuint dwOption);
    bool SetMaterialOption();

    bool AddTexture(LTextureCreator TextureCreator);

private:
    std::vector<LTextureCreator> m_vecTextures;
    L3DMATERIAL m_Material;
    GLuint m_dwOption;
    GLuint m_dwMaterialOptionCount;
    GLuint m_dwNumMaterials;
};

#endif // !_LMATERIAL_CREATOR_H_
