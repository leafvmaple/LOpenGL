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
#include "LDefine.h"
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
    
    uOffset += sizeof(FileHead) + sizeof(MeshHead);
    
    MeshHead.Blocks.PositionBlock = uOffset;
    uOffset += nNumVerties * sizeof(GLVec3);
    
    if (m_Normals.size() > 0)
    {
        MeshHead.Blocks.NormalBlock = uOffset;
        uOffset += nNumVerties * sizeof(GLVec3);
    }
    
    if (m_Diffuses.size() > 0)
    {
        MeshHead.Blocks.DiffuseBlock = uOffset;
        uOffset += nNumVerties * sizeof(DWORD);
    }
    
    if (m_Textures.size() > 0)
    {
        MeshHead.Blocks.TextureUVW1Block = uOffset;
        uOffset += nNumVerties * sizeof(GLUVW3);
    }
    
    if (m_Faces.size() > 0)
    {
        MeshHead.Blocks.FacesIndexBlock = uOffset;
        uOffset += nNumFaces * sizeof(GLInt3);
    }
    
    fwrite(&FileHead, sizeof(FileHead), 1, pFile);
    fwrite(&MeshHead, sizeof(MeshHead), 1, pFile);
    fwrite(&m_Verties[0], sizeof(GLVec3), nNumVerties, pFile);
    
    if (m_Normals.size() > 0)
        fwrite(&m_Normals[0], sizeof(GLVec3), nNumVerties, pFile);
    if (m_Diffuses.size() > 0)
        fwrite(&m_Diffuses[0], sizeof(GLCOLOR), nNumVerties, pFile);
    if (m_Textures.size() > 0)
        fwrite(&m_Textures[0], sizeof(GLUVW3), nNumVerties, pFile);
    if (m_Faces.size() > 0)
        fwrite(&m_Faces[0], sizeof(GLInt3), nNumFaces, pFile);
    
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

bool LMeshCreator::AddDiffuseVerties(GL_VERTEX* pVerties, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Verties.push_back(pVerties[i].Vertex);
        m_Diffuses.push_back(L3DCOLOR_COLORVALUE(pVerties[i].Diffuse.x,
                                                 pVerties[i].Diffuse.y,
                                                 pVerties[i].Diffuse.z, 1));
        m_Textures.push_back(pVerties[i].Texture);
    }
    return true;
}

bool LMeshCreator::AddFaces(GLInt3* pFaces, unsigned int nCount /*= 1*/)
{
    for (int i = 0; i < nCount; i++)
    {
        m_Faces.push_back(pFaces[i]);
    }
    
    return true;
}

