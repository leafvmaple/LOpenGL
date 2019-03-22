#include <stdlib.h>

#include "L3DModel.h"
#include "L3DShader.h"
#include "L3DTexture.h"
#include "L3DMesh.h"

L3DModel::L3DModel()
: m_nVertexArrObj(0)
, m_nVertexBufObj(0)
, m_nElemBufObj(0)
, m_dwSubsetCount(0)
{
}


L3DModel::~L3DModel()
{
    Uninit();
}

bool L3DModel::Init(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;

    m_dwSubsetCount = 1;

    bRetCode = LoadModel(cszFileName);
    BOOL_ERROR_EXIT(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}

void L3DModel::Uninit()
{
    m_nVertexArrObj = 0;
    m_nVertexBufObj = 0;
    m_nElemBufObj = 0;
}

bool L3DModel::LoadModel(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;

    const LoadModelFunc* pMeshFunc = GetLoadModelFunc(cszFileName);
    BOOL_ERROR_EXIT(pMeshFunc);

    bRetCode = (this->*(pMeshFunc->fnLoadMesh))(cszFileName);
    BOOL_ERROR_EXIT(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}

bool L3DModel::LoadMesh(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;

    m_p3DMesh = new L3DMesh;
    BOOL_ERROR_EXIT(m_p3DMesh);

    bRetCode = m_p3DMesh->LoadMesh(cszFileName);
    BOOL_ERROR_EXIT(bRetCode);

    bResult = true;
Exit0:
    return bResult;
}

bool L3DModel::LoadMaterial(const char* cszFileName)
{
    return false;
}

bool L3DModel::LoadTexture(const char* cszFileName)
{
    return false;
}

bool L3DModel::LoadParticle(const char* cszFileName)
{
    return false;
}

bool L3DModel::UpdatePosition(L3DCamera* p3DCamera)
{
    if (m_p3DMesh)
        m_p3DMesh->UpdatePosition(p3DCamera);
    return true;
}

bool L3DModel::UpdateDisplay()
{
    bool bResult = false;
    bool bRetCode = false;

    for (GLuint u = 0; u < m_dwSubsetCount; u++)
    {
        bRetCode = UpdateMesh(u);
    }

    bResult = true;
Exit0:
    return bResult;
}

bool L3DModel::UpdateMesh(GLuint uIndex)
{
    if (m_p3DMesh)
        m_p3DMesh->UpdateMesh(uIndex);
    return true;
}

bool L3DModel::UpdateMaterial(GLuint uIndex)
{
    return false;
}

const L3DModel::LoadModelFunc* L3DModel::GetLoadModelFunc(const char* cszFileName)
{
    const LoadModelFunc *pReturn = NULL;
    size_t uSize = sizeof(s_ModelLoadFunc) / sizeof(LoadModelFunc);
    size_t i = 0;
    
    for (; i < uSize; i++)
    {
        if (strstr(cszFileName, s_ModelLoadFunc[i].pwcsFileExt))
            break;
    }
    BOOL_ERROR_RETURN(i != uSize);
    
    pReturn = &s_ModelLoadFunc[i];
    return pReturn;
}
