#ifndef _LTEXTURE_CREATOR_H_
#define _LTEXTURE_CREATOR_H_

#include "LDefine.h"
#include "L3DTexture.h"

class LTextureCreator
{
public:
    LTextureCreator();
    ~LTextureCreator();

    bool Init();
    bool Create(FILE* pFile);

    bool SetImagePath(char* pcszFileName);

private:
    L3DTexture::_TEXTURE m_Texture;
};

#endif // !_LTEXTURE_CREATOR_H_