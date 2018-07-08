#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "L3DMaterial.h"
#include "LMaterialCreator.h"

LMaterialCreator::LMaterialCreator()
: m_dwOption(0)
, m_dwMaterialOptionCount(0)
, m_dwNumMaterials(0)
{
    Init();
}

LMaterialCreator::~LMaterialCreator()
{

}

bool LMaterialCreator::Init()
{
    memset(&m_Material, 0, sizeof(m_Material));
    m_dwNumMaterials = 1;

    return false;
}

bool LMaterialCreator::Create(const char* cszFileName)
{
    unsigned int uOffset = 0;
    FILE* pFile = fopen(cszFileName, "wb");

    GLuint dwMask = 0x4D41544C;
    fwrite(&dwMask, sizeof(dwMask), 1, pFile);

    GLuint dwBlockLength = 0;
    fwrite(&dwBlockLength, sizeof(dwBlockLength), 1, pFile);
    fwrite(&m_dwNumMaterials, sizeof(m_dwNumMaterials), 1, pFile);

    fwrite(&m_Material.Ambient, sizeof(m_Material.Ambient), 1, pFile);
    fwrite(&m_Material.Diffuse, sizeof(m_Material.Diffuse), 1, pFile);
    fwrite(&m_Material.Specular, sizeof(m_Material.Specular), 1, pFile);
    fwrite(&m_Material.Emissive, sizeof(m_Material.Emissive), 1, pFile);
    fwrite(&m_Material.Power, sizeof(m_Material.Power), 1, pFile);
    fwrite(&m_dwOption, sizeof(m_dwOption), 1, pFile);
    fwrite(&m_dwMaterialOptionCount, sizeof(m_dwMaterialOptionCount), 1, pFile);

    for (int i = 0; i < m_dwMaterialOptionCount; i++)
    {

    }

    GLuint dwNumUsedTexture = m_vecTextures.size();
    fwrite(&dwNumUsedTexture, sizeof(dwNumUsedTexture), 1, pFile);
    for (int i = 0; i < dwNumUsedTexture; i++)
    {
        m_vecTextures[i].Create(pFile);
    }

    fclose(pFile);

    return true;
}

bool LMaterialCreator::SetMaterial(L3DMATERIAL* pMaterial)
{
    m_Material = *pMaterial;
    return true;
}

bool LMaterialCreator::SetOption(GLuint dwOption)
{
    m_dwOption = dwOption;
    return true;
}

bool LMaterialCreator::AddTexture(LTextureCreator TextureCreator)
{
    m_vecTextures.push_back(TextureCreator);
    return true;
}
