#include <cstring>

#include "LTextureCreator.h"
#include "L3DTexture.h"

LTextureCreator::LTextureCreator()
{
    Init();
}

LTextureCreator::~LTextureCreator()
{

}

bool LTextureCreator::Init()
{
    memset(&m_Texture, 0, sizeof(m_Texture));
    return true;
}

bool LTextureCreator::Create(FILE* pFile)
{
    fwrite(&m_Texture, sizeof(m_Texture), 1, pFile);
    return true;
}

bool LTextureCreator::SetImagePath(char* pcszFileName)
{
    strcpy(m_Texture.szTextureFileName, "texture/");
    strcat(m_Texture.szTextureFileName, pcszFileName);
    return true;
}
