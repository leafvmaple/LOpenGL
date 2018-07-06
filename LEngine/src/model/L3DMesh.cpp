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
, m_dwNumFaces(0)
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
    glBindVertexArray(m_nVertexArrObj);
    glDrawElements(GL_TRIANGLES, m_dwNumFaces, GL_UNSIGNED_SHORT, 0);

    return true;
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
        
        unsigned short* pwIndices = new unsigned short[pLMeshData->dwNumFaces * 3];
        for(unsigned int i = 0; i < pLMeshData->dwNumFaces; i++)
        {
            pwIndices[i * 3]     = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3]);
            pwIndices[i * 3 + 1] = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3 + 1]);
            pwIndices[i * 3 + 2] = static_cast<unsigned short>(pLMeshData->pFaceIndices[i * 3 + 2]);
        }
        
        m_dwNumFaces = pLMeshData->dwNumFaces * 3;
        
        glGenVertexArrays(1, &m_nVertexArrObj);
        
        unsigned int nVertexBufObj = 0;
        glGenBuffers(1, &nVertexBufObj);
        unsigned int nElemBufObj = 0;
        glGenBuffers(1, &nElemBufObj);
        
        glBindVertexArray(m_nVertexArrObj);
        glBindBuffer(GL_ARRAY_BUFFER, nVertexBufObj);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nElemBufObj);
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(pbyVertices), pbyVertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pwIndices), pwIndices, GL_STATIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, dwVertexStride, (void*)0);
        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        bResult = true;
    } while (0);
    
    return bResult;
}
