//
//  L3DMesh.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/05.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <memory.h>
#include "L3DMesh.h"
#include "L3DMaterial.h"
#include "io/LFileReader.h"

L3DMesh::L3DMesh()
: m_pLMaterial(nullptr)
, m_nVertexArrObj(0)
, m_dwNumFaces(0)
{
    
}

L3DMesh::~L3DMesh()
{
    
}

const VertexFromatOffsetItem* L3DMesh::GetVertexFormat(GLuint dwFVF)
{
    const VertexFromatOffsetItem *pReturn = NULL;
    size_t uSize = sizeof(s_VertexFormat) / sizeof(VertexFromatOffsetItem);
    size_t i = 0;
    for (; i < uSize; i++)
    {
        if (s_VertexFormat[i].dwFVF == dwFVF)
            break;
    }
    BOOL_ERROR_RETURN(i != uSize);
    
    pReturn = &s_VertexFormat[i];
    return pReturn;
}

GLuint L3DMesh::GetVertexStride(GLuint dwFVF)
{
    GLuint dwStride = 0;
    const VertexFromatOffsetItem *pVertexFromatItem = GetVertexFormat(dwFVF);
    BOOL_ERROR_RETURN(pVertexFromatItem);
    
    dwStride = pVertexFromatItem->dwDestOffset[pVertexFromatItem->dwNumElement - 1] +
    pVertexFromatItem->dwDestStride[pVertexFromatItem->dwNumElement - 1];
    
    return dwStride;
}

bool L3DMesh::LoadMesh(const char* cszFileName)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        LMESH_DATA MeshData;
        bRetCode = LoadMeshData(cszFileName, &MeshData);
        BOOL_ERROR_BREAK(bRetCode);
        
        bRetCode = CreateMesh(&MeshData);
        BOOL_ERROR_BREAK(bRetCode);
        
        char cszMtl[FILENAME_MAX];
        strcpy(cszMtl, cszFileName);
        strcpy(cszMtl + strlen(cszMtl) - 5, ".mtl");
        
        if (LFileReader::IsExist(cszMtl))
        {
            m_pLMaterial = new L3DMaterial;
            BOOL_ERROR_BREAK(m_pLMaterial);
            
            bRetCode = m_pLMaterial->LoadLMaterial(cszMtl);
            BOOL_ERROR_BREAK(bRetCode);
        }
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMesh::UpdateMesh(GLuint dwSubMesh)
{
    if (m_pLMaterial)
        m_pLMaterial->UpdateMaterial(dwSubMesh);
    
    glBindVertexArray(m_nVertexArrObj);
    glDrawElements(GL_TRIANGLES, m_dwNumFaces, GL_UNSIGNED_SHORT, 0);

    return true;
}

bool L3DMesh::UpdatePosition(L3DCamera *p3DCamera)
{
    if (m_pLMaterial)
        m_pLMaterial->UpdatePosition(p3DCamera);
    return true;
}

bool L3DMesh::LoadMeshData(const char* cszFileName, LMESH_DATA* pLMeshData)
{
    bool bResult = false;
    
    do
    {
        memset(pLMeshData, 0, sizeof(LMESH_DATA));
        
        GLubyte* pbyMesh = NULL;
        size_t uMeshLen = 0;
        LFileReader::Reader(cszFileName, &pbyMesh, &uMeshLen);
        GLubyte* pbyBufferHead = pbyMesh;
        
        _MeshFileHead* pMeshFileHead = NULL;
        pbyMesh = LFileReader::Convert(pbyMesh, pMeshFileHead);
        BOOL_ERROR_BREAK(pMeshFileHead->dwFileMask == 0x4D455348);
        BOOL_ERROR_BREAK(pMeshFileHead->dwVersion == 0);
        
        _MeshHead* pMeshHead = NULL;
        pbyMesh = LFileReader::Convert(pbyMesh, pMeshHead);
        pLMeshData->dwNumVertices = pMeshHead->dwNumVertices;
        pLMeshData->dwNumFaces    = pMeshHead->dwNumFaces;
        pLMeshData->dwNumSubset   = pMeshHead->dwNumSubset;
        
        if (pMeshHead->Blocks.PositionBlock)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.PositionBlock, pLMeshData->pPos, pMeshHead->dwNumVertices);
            pLMeshData->dwMeshFVF |= L3DFVF_XYZ;

            //pLMesh->BoundingBox.AddPosition(pMeshData->pPos, pMeshData->dwNumVertices);
        }

        if (pMeshHead->Blocks.NormalBlock)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.NormalBlock, pLMeshData->pNormals, pMeshHead->dwNumVertices);
            pLMeshData->dwMeshFVF |= L3DFVF_NORMAL;
        }

        if (pMeshHead->Blocks.DiffuseBlock)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.DiffuseBlock, pLMeshData->pDiffuse, pMeshHead->dwNumVertices);
            pLMeshData->dwMeshFVF |= L3DFVF_DIFFUSE;
        }

        if (pMeshHead->Blocks.TextureUVW1Block)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.TextureUVW1Block, pLMeshData->pUV1, pMeshHead->dwNumVertices);
            pLMeshData->dwMeshFVF |= L3DFVF_TEX1;

            //计算UVSizeMax
            //BBox UVBox;
            //UVBox.AddPosition(pMeshData->pUV1, pMeshHead->dwNumVertices);
            //pMeshData->pUVSizeMax[0].x = fabs(UVBox.A.x) > fabs(UVBox.B.x) ? fabs(UVBox.A.x) : fabs(UVBox.B.x);
            //pMeshData->pUVSizeMax[0].y = fabs(UVBox.A.y) > fabs(UVBox.B.y) ? fabs(UVBox.A.y) : fabs(UVBox.B.y);
        }
        
        if (pMeshHead->Blocks.FacesIndexBlock)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.FacesIndexBlock, pLMeshData->pFaceIndices, 3 * pMeshHead->dwNumFaces);
        }
        
        if (pMeshHead->Blocks.SubsetIndexBlock)
        {
            LFileReader::Convert(pbyBufferHead + pMeshHead->Blocks.SubsetIndexBlock, pLMeshData->pSubsetIndices, pMeshHead->dwNumFaces);
        }
        
        pLMeshData->pbyFileBuffer = pbyBufferHead;
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMesh::CreateMesh(const LMESH_DATA* pLMeshData)
{
    bool bResult = false;
    bool bRetCode = false;
    
    do
    {
        const VertexFromatOffsetItem *pVertexFormat = GetVertexFormat(pLMeshData->dwMeshFVF);
        BOOL_ERROR_BREAK(pVertexFormat);
        
        GLuint dwVertexStride = GetVertexStride(pLMeshData->dwMeshFVF);
        
        GLubyte* pbyVertices = new GLubyte[pLMeshData->dwNumVertices * dwVertexStride];
        
        for (GLuint i = 0; i < pLMeshData->dwNumVertices; i++)
        {
            GLubyte* pCurrentVertexData = pbyVertices + dwVertexStride * i;
            for (GLuint j = 0; j < pVertexFormat->dwNumElement; j++)
            {
                const GLubyte* pCurrentSrc = *(reinterpret_cast<GLubyte* const*>(&pLMeshData->pPos) + pVertexFormat->dwSrcOffset[j]);
                memcpy(pCurrentVertexData + pVertexFormat->dwDestOffset[j],
                       pCurrentSrc + pVertexFormat->dwSrcStride[j] * i,
                       pVertexFormat->dwDestStride[j]);
                if (pVertexFormat->dwElementFVF[j] == L3DFVF_DIFFUSE)
                {
                    const GLuint* pSrcDiffuse = reinterpret_cast<const GLuint*>(
                                                pCurrentSrc + pVertexFormat->dwSrcStride[j] * i);
                    LCOLOR_RGBA_FLOAT* pDestDiffuse = reinterpret_cast<LCOLOR_RGBA_FLOAT*>(
                                                pCurrentVertexData + pVertexFormat->dwDestOffset[j]);
                    *pDestDiffuse = L3DARGB_COLOR(*pSrcDiffuse);
                }
            }
        }
        
        GLushort* pwIndices = new GLushort[pLMeshData->dwNumFaces * 3];
        for(GLuint i = 0; i < pLMeshData->dwNumFaces; i++)
        {
            pwIndices[i * 3]     = static_cast<GLushort>(pLMeshData->pFaceIndices[i * 3]);
            pwIndices[i * 3 + 1] = static_cast<GLushort>(pLMeshData->pFaceIndices[i * 3 + 1]);
            pwIndices[i * 3 + 2] = static_cast<GLushort>(pLMeshData->pFaceIndices[i * 3 + 2]);
        }
        
        m_dwNumFaces = pLMeshData->dwNumFaces * 3;
        
        glGenVertexArrays(1, &m_nVertexArrObj);
        
        GLuint nVertexBufObj = 0;
        glGenBuffers(1, &nVertexBufObj);
        GLuint nElemBufObj = 0;
        glGenBuffers(1, &nElemBufObj);
        
        glBindVertexArray(m_nVertexArrObj);
        glBindBuffer(GL_ARRAY_BUFFER, nVertexBufObj);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nElemBufObj);
        
        glBufferData(GL_ARRAY_BUFFER, pLMeshData->dwNumVertices * dwVertexStride, pbyVertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_dwNumFaces * sizeof(GLushort), pwIndices, GL_STATIC_DRAW);
        
        for (GLuint i = 0; i < pVertexFormat->dwNumElement; i++)
        {
            glVertexAttribPointer(i, pVertexFormat->dwDestStride[i] / 4,
                                  GL_FLOAT, GL_FALSE, dwVertexStride,
                                  (void*)pVertexFormat->dwDestOffset[i]);
            glEnableVertexAttribArray(i);
        }

        bResult = true;
    } while (0);
    
    return bResult;
}
