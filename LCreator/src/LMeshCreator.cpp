//
//  LMeshCreator.cpp
//  LCreator
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include "LMeshCreator.h"

LMeshCreator::LMeshCreator()
{
    
}

LMeshCreator::~LMeshCreator()
{
    
}

bool LMeshCreator::Init()
{
    memset(&m_FileHead, 0, sizeof(m_FileHead));
    
    m_FileHead.dwFileMask = 0x4D455348;
    m_FileHead.dwVersion = 0;
    
    memset(&m_MeshHead, 0, sizeof(m_MeshHead));
    
    m_Verties.clear();
    m_Faces.clear();
    
    return true;
}

bool LMeshCreator::Create(const char *cszFileName)
{
    unsigned int uOffset = 0;
    int nNumFaces = m_Faces.size();
    int nNumVerties = m_Verties.size();
    FILE* pFile = fopen(cszFileName, "wb");
    
    m_MeshHead.dwNumSubset = 1;
    m_MeshHead.dwNumFaces = nNumFaces;
    m_MeshHead.dwNumVertices = nNumVerties;
    
    BYTE* pNormals = new BYTE[nNumVerties * sizeof(GLVec3)];
    BYTE* pTexture1 = new BYTE[nNumVerties * sizeof(GLTEX2)];
    
    m_MeshHead.Blocks.PositionBlock = sizeof(m_FileHead) + sizeof(m_MeshHead);
    m_MeshHead.Blocks.NormalBlock = m_MeshHead.Blocks.PositionBlock + nNumVerties * sizeof(GLVec3);
    m_MeshHead.Blocks.TextureUVW1Block = m_MeshHead.Blocks.NormalBlock + nNumVerties * sizeof(GLVec3);
    m_MeshHead.Blocks.FacesIndexBlock = m_MeshHead.Blocks.TextureUVW1Block + nNumVerties * sizeof(GLTEX2);
    
    fwrite(&m_FileHead, sizeof(m_FileHead), 1, pFile);
    fwrite(&m_MeshHead, sizeof(m_MeshHead), 1, pFile);
    fwrite(&m_Verties, nNumVerties * sizeof(GLVec3), 1, pFile);
    fwrite(pNormals, nNumVerties * sizeof(GLVec3), 1, pFile);
    fwrite(pTexture1, nNumVerties * sizeof(GLTEX2), 1, pFile);
    fwrite(&m_Faces, nNumFaces * sizeof(GLFace3), 1, pFile);
    
    fclose(pFile);
    
    return true;
}

bool LMeshCreator::AddVerex(GLVec3* pVertex)
{
    m_Verties.push_back(*pVertex);
    return true;
}

bool LMeshCreator::AddVerties(GLVec3* pVerties, unsigned int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Verties.push_back(pVerties[i]);
    }
    
    return true;
}

bool LMeshCreator::AddFace(GLFace3* pFace)
{
    m_Faces.push_back(*pFace);
    return true;
}

bool LMeshCreator::AddFaces(GLFace3* pFaces, unsigned int nCount)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Faces.push_back(pFaces[i]);
    }
    
    return true;
}
