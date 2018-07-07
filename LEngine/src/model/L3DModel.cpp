#include <stdlib.h>

#include "L3DModel.h"
#include "shader/L3DShader.h"
#include "L3DTexture.h"
#include "L3DMesh.h"

L3DModel::L3DModel()
: m_nVertexArrObj(0)
, m_nVertexBufObj(0)
, m_nElemBufObj(0)
, m_dwSubsetCount(0)
, m_p3DShader(nullptr)
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

    do 
    {
        m_dwSubsetCount = 1;

        bRetCode = LoadModel(cszFileName);
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
}

void L3DModel::Uninit()
{
    m_nVertexArrObj = 0;
    m_nVertexBufObj = 0;
    m_nElemBufObj = 0;

    if (m_p3DShader)
    {
        SAFE_DELETE(m_p3DShader);
    }
}

bool L3DModel::LoadModel(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        const LoadModelFunc* pMeshFunc = GetLoadModelFunc(cszFileName);
        BOOL_ERROR_BREAK(pMeshFunc);
        
        bRetCode = (this->*(pMeshFunc->fnLoadMesh))(cszFileName);
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DModel::LoadMesh(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        m_p3DMesh = new L3DMesh;
        BOOL_ERROR_BREAK(m_p3DMesh);
        
        bRetCode = m_p3DMesh->LoadMesh(cszFileName);
        BOOL_ERROR_BREAK(bRetCode);
        
        m_p3DShader = new L3DShader;
        BOOL_ERROR_BREAK(m_p3DShader);
        
        bRetCode = m_p3DShader->LoadShader("res/shader/default.vs", "res/shader/default.fs");
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
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

bool L3DModel::LoadShader(const char* pVertexPath, const char* pFragmentPath)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        m_p3DShader = new L3DShader;
        BOOL_ERROR_BREAK(m_p3DShader);
        
        bRetCode = m_p3DShader->LoadShader(pVertexPath, pFragmentPath);
        BOOL_ERROR_BREAK(bRetCode);
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DModel::UpdateDisplay()
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        bRetCode = UpdateShader();
        BOOL_ERROR_BREAK(bRetCode);

        for (unsigned int u = 0; u < m_dwSubsetCount; u++)
        {
            bRetCode = UpdateMesh(u);
            BOOL_ERROR_BREAK(bRetCode);
        }

        bResult = true;
    } while (0);

    return bResult;
}

bool L3DModel::UpdateMesh(unsigned int uIndex)
{
    if (m_p3DMesh)
        m_p3DMesh->UpdateMesh(uIndex);
    return true;
}

bool L3DModel::UpdateMaterial(unsigned int uIndex)
{
    return false;
}

bool L3DModel::UpdateShader()
{
    if (m_p3DShader)
        m_p3DShader->UpdateShader();
    return true;
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
