#include <stdlib.h>

#include "L3DModel.h"
#include "shader/L3DShader.h"
#include "L3DTexture.h"
#include "L3DMesh.h"

L3DModel::L3DModel()
: m_nVertexArrObj(0)
, m_nVertexBufObj(0)
, m_nElemBufObj(0)
, m_p3DShader(nullptr)
{
}


L3DModel::~L3DModel()
{
    Uninit();
}

bool L3DModel::Init(const void* pModelVerteices,
                    GLsizeiptr nVerticesCount,
                    const void* pModelIndices,
                    GLsizeiptr nIndicesCount,
                    const char *pVertexPath,
                    const char *pFragmentPath)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        bRetCode = InitVertex(pModelVerteices, nVerticesCount, pModelIndices, nIndicesCount);
        BOOL_ERROR_BREAK(bRetCode);

        bRetCode = InitShader(pVertexPath, pFragmentPath);
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

bool L3DModel::InitVertex(const void* pModelVertices,
                          GLsizeiptr nVerticesCount,
                          const void* pModelIndices,
                          GLsizeiptr nIndicesCount)
{
    bool bResult = false;

    do 
    {
        glGenVertexArrays(1, &m_nVertexArrObj);
        glGenBuffers(1, &m_nVertexBufObj);
        glGenBuffers(1, &m_nElemBufObj);

        glBindVertexArray(m_nVertexArrObj);

        glBindBuffer(GL_ARRAY_BUFFER, m_nVertexBufObj);
        glBufferData(GL_ARRAY_BUFFER, nVerticesCount, pModelVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElemBufObj);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndicesCount, pModelIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);

        bResult = true;
    } while (0);

    return bResult;
}

bool L3DModel::InitShader(const char* pVertexPath, const char* pFragmentPath)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        m_p3DShader = new L3DShader;
        BOOL_ERROR_BREAK(m_p3DShader);

        bRetCode = m_p3DShader->Init(pVertexPath, pFragmentPath);
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
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

bool L3DModel::UpdateDisplay()
{
    bool bResult = false;

    do 
    {
        if (m_p3DShader)
        {
            m_p3DShader->User();
        }
        glBindVertexArray(m_nVertexArrObj);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        bResult = true;
    } while (0);

    return bResult;
}

const L3DModel::LoadModelFunc* L3DModel::GetLoadModelFunc(const char* cszFileName)
{
    const LoadModelFunc *pReturn = NULL;
    size_t uSize = sizeof(s_ModelLoadFunc) / sizeof(LoadModelFunc);
    size_t i = 0;
    for (; i < uSize; i++)
    {
        if (!strstr(cszFileName, s_ModelLoadFunc[i].pwcsFileExt))
            break;
    }
    BOOL_ERROR_RETURN(i != uSize);
    
    pReturn = &s_ModelLoadFunc[i];
    return pReturn;
}
