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
    Init();
}

LMeshCreator::~LMeshCreator()
{
    
}

bool LMeshCreator::Init()
{
    m_Verties.clear();
    m_Faces.clear();
    m_Normals.clear();
    m_Textures.clear();
    
    return true;
}

bool LMeshCreator::Create(const char *cszFileName)
{
    unsigned int uOffset = 0;
    int nNumFaces = m_Faces.size();
    int nNumVerties = m_Verties.size();
    FILE* pFile = fopen(cszFileName, "wb");

    _MeshFileHead FileHead;
    memset(&FileHead, 0, sizeof(FileHead));
    FileHead.dwFileMask = 0x4D455348;
    FileHead.dwVersion = 0;
    
    _MeshHead MeshHead;
    memset(&MeshHead, 0, sizeof(MeshHead));
    MeshHead.dwNumSubset = 1;
    MeshHead.dwNumFaces = nNumFaces;
    MeshHead.dwNumVertices = nNumVerties;
    
    MeshHead.Blocks.PositionBlock = sizeof(FileHead) + sizeof(MeshHead);
    MeshHead.Blocks.NormalBlock = MeshHead.Blocks.PositionBlock + nNumVerties * sizeof(GLVec3);
    MeshHead.Blocks.TextureUVW1Block = MeshHead.Blocks.NormalBlock + nNumVerties * sizeof(GLVec3);
    MeshHead.Blocks.FacesIndexBlock = MeshHead.Blocks.TextureUVW1Block + nNumVerties * sizeof(GLTEX2);

    BYTE* pNormals = new BYTE[nNumVerties * sizeof(GLVec3)];
    if (m_Normals.size() > 0)
        memcpy(pNormals, &m_Normals[0], m_Normals.size() * sizeof(GLVec3));
    BYTE* pTexture1 = new BYTE[nNumVerties * sizeof(GLTEX2)];
    if (m_Textures.size() > 0)
        memcpy(pTexture1, &m_Textures[0], m_Textures.size() * sizeof(GLTEX2));
    
    fwrite(&FileHead, sizeof(FileHead), 1, pFile);
    fwrite(&MeshHead, sizeof(MeshHead), 1, pFile);
    fwrite(&m_Verties[0], nNumVerties * sizeof(GLVec3), 1, pFile);
    fwrite(pNormals, nNumVerties * sizeof(GLVec3), 1, pFile);
    fwrite(pTexture1, nNumVerties * sizeof(GLTEX2), 1, pFile);
    fwrite(&m_Faces[0], nNumFaces * sizeof(GLFace3), 1, pFile);
    
    fclose(pFile);
    
    return true;
}

bool LMeshCreator::AddVerties(GLVec3* pVerties, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Verties.push_back(pVerties[i]);
    }
    
    return true;
}

bool LMeshCreator::AddFaces(GLFace3* pFaces, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Faces.push_back(pFaces[i]);
    }
    
    return true;
}

bool LMeshCreator::AddNomals(GLVec3* pNomals, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Normals.push_back(pNomals[i]);
    }

    return true;
}

bool LMeshCreator::AddTextures(GLTEX2* pTextures, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Textures.push_back(pTextures[i]);
    }

    return true;
}
