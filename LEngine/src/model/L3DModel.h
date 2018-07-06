
#ifndef _LMODEL_H_
#define _LMODEL_H_

#include "LInterface.h"

class L3DMesh;
class L3DShader;
class L3DTexture;

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
    bool Init(const void* pModelVertices,
              GLsizeiptr nVerticesCount,
              const void* pModelIndices,
              GLsizeiptr nIndicesCount,
              const char *pVertexPath,
              const char *pFragmentPath);

    void Uninit();
    
    bool LoadModel(const char* cszFileName);
    bool LoadMesh(const char* cszFileName);
    bool LoadTexture(const char* cszFileName);
    bool LoadMaterial(const char* cszFileName);
    bool LoadParticle(const char* cszFileName);

    bool InitVertex(const void* pModelVertices,
                    GLsizeiptr nVerteicesCount,
                    const void* pModelIndices,
                    GLsizeiptr nIndicesCount);

    bool InitShader(const char *pVertexShaderSource,
                    const char *pFragmentShaderSource);

public:
    bool UpdateDisplay();
    bool UpdateMesh(DWORD uIndex);
    bool UpdateMaterial(DWORD uIndex);

private:
    L3DMesh* m_p3DMesh;
    L3DShader* m_p3DShader;
    L3DTexture* m_pLTexture;

    unsigned int m_dwSubsetCount;

    unsigned int m_nVertexArrObj;
    unsigned int m_nVertexBufObj;
    unsigned int m_nElemBufObj;
    
    static const LoadModelFunc* GetLoadModelFunc(const char* cszFileName);
};

static L3DModel::LoadModelFunc s_ModelLoadFunc[] = {
    {".mesh", &L3DModel::LoadMesh},
    {".mtl",  &L3DModel::LoadMaterial},
    {".pss",  &L3DModel::LoadParticle},
};

#endif
