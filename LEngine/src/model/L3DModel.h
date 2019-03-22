
#ifndef _LMODEL_H_
#define _LMODEL_H_

#include "LInterface.h"

class L3DMesh;
class L3DShader;
class L3DTexture;
class L3DCamera;

class L3DModel : public ILModel
{
public:
    struct LoadModelFunc
    {
        const char* pwcsFileExt;
        bool (L3DModel::*fnLoadMesh)(const char* cszFileName);
    };
    
public:
    L3DModel();
    ~L3DModel();

    bool Init(const char* cszFileName);
    void Uninit();
    
    bool LoadModel(const char* cszFileName);
    bool LoadMesh(const char* cszFileName);
    bool LoadTexture(const char* cszFileName);
    bool LoadMaterial(const char* cszFileName);
    bool LoadParticle(const char* cszFileName);

public:
    bool UpdatePosition(L3DCamera* p3DCamera);
    bool UpdateDisplay();
    bool UpdateMesh(GLuint uIndex);
    bool UpdateMaterial(GLuint uIndex);

private:
    L3DMesh*    m_p3DMesh;
    L3DTexture* m_pLTexture;

    GLuint m_dwSubsetCount;

    GLuint m_nVertexArrObj;
    GLuint m_nVertexBufObj;
    GLuint m_nElemBufObj;
    
    static const LoadModelFunc* GetLoadModelFunc(const char* cszFileName);
};

static L3DModel::LoadModelFunc s_ModelLoadFunc[] = {
    {".mesh", &L3DModel::LoadMesh},
    {".mtl",  &L3DModel::LoadMaterial},
    {".pss",  &L3DModel::LoadParticle},
};

#endif
