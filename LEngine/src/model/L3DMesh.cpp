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
{
    
}

L3DMesh::~L3DMesh()
{
    
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
        
        pLMeshData->pbyFileBuffer = pbyBufferHead;
        
        bResult = true;
    } while (0);
    
    return bResult;
}

bool L3DMesh::CreateMesh(const LMESH_DATA* pLMeshData)
{
    return false;
}
