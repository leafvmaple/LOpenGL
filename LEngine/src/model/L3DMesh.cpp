//
//  L3DMesh.cpp
//  LEngine
//
//  Created by LeafMaple on 2018/07/05.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <memory.h>
#include "L3DMesh.h"
#include "io/LFileReader.h"

L3DMesh::L3DMesh()
: m_nVertexArrObj(0)
, m_nVertexBufObj(0)
, m_nElemBufObj(0)
{
    
}

L3DMesh::~L3DMesh()
{
    
}

const VertexFromatOffsetItem* L3DMesh::GetVertexFormat(unsigned int dwFVF)
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

unsigned int L3DMesh::GetVertexStride(unsigned int dwFVF)
{
    unsigned int dwStride = 0;
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
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMesh::UpdateMesh(unsigned int dwSubMesh)
{
    return false;
}

bool L3DMesh::LoadMeshData(const char* cszFileName, LMESH_DATA* pLMeshData)
{
    bool bResult = false;
    
    do
    {
        memset(pLMeshData, 0, sizeof(LMESH_DATA));
        
        BYTE* pbyMesh = NULL;
        size_t uMeshLen = 0;
        LFileReader::Reader(cszFileName, &pbyMesh, &uMeshLen);
        BYTE* pbyBufferHead = pbyMesh;
        
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
            
            //pLMesh->BoundingBox.AddPosition(pMeshData->pPos, pMeshData->dwNumVertices);
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
        
        unsigned int dwVertexStride = GetVertexStride(pLMeshData->dwMeshFVF);
        
        BYTE* pbyVertices = new BYTE[pLMeshData->dwNumVertices * dwVertexStride];
        
        for (unsigned int i = 0; i < pLMeshData->dwNumVertices; i++)
        {
            BYTE* pCurrentVertexData = pbyVertices + dwVertexStride * i;
            for (unsigned int j = 0; j < pVertexFormat->dwNumElement; j++)
            {
                const BYTE* pCurrentSrc = *(reinterpret_cast<BYTE* const*>(&pLMeshData->pPos) + pVertexFormat->dwSrcOffset[j]);
                memcpy(pCurrentVertexData + pVertexFormat->dwDestOffset[j],
                       pCurrentSrc + pVertexFormat->dwSrcStride[j] * i,
                       pVertexFormat->dwDestStride[j]);
            }
        }
        
        unsigned short* pwIndices = NULL;
        for(unsigned int i = 0; i < pLMeshData->dwNumFaces; i++)
        {
            pwIndices[i * 3]     = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3]);
            pwIndices[i * 3 + 1] = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3 + 1]);
            pwIndices[i * 3 + 2] = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3 + 2]);
        }
        
        glGenVertexArrays(1, &m_nVertexArrObj);
        glGenBuffers(1, &m_nVertexBufObj);
        glGenBuffers(1, &m_nElemBufObj);
        
        glBindVertexArray(m_nVertexArrObj);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_nVertexBufObj);
        glBufferData(GL_ARRAY_BUFFER, pLMeshData->dwNumVertices, pbyVertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElemBufObj);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pLMeshData->dwNumFaces, pwIndices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        
        bResult = true;
    } while (0);
    
    return bResult;
}
