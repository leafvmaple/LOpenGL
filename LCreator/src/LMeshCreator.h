//
//  LMeshCreator.h
//  LCreator
//
//  Created by LeafMaple on 2018/07/07.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifndef LMeshCreator_h
#define LMeshCreator_h

#include "io/LFileStruct.h"
#include "LInterface.h"
#include <vector>

typedef struct GLFace3
{
    unsigned int x;
    unsigned int y;
    unsigned int z;
} GLFace3;

typedef struct GLTEX2
{
    float u;
    float v;
} GLTEX2;

class LMeshCreator
{
public:
    LMeshCreator();
    ~LMeshCreator();
    
    bool Init();
    bool Create(const char* cszFileName);
    
    bool AddVerex(GLVec3* pVertex);
    bool AddVerties(GLVec3* pVerties, unsigned int nCount);
    
    bool AddFace(GLFace3* pFace);
    bool AddFaces(GLFace3* pFaces, unsigned int nCount);
    
private:
    _MeshFileHead m_FileHead;
    _MeshHead m_MeshHead;
    
    std::vector<GLVec3> m_Verties;
    std::vector<GLFace3> m_Faces;
};

#endif /* LMeshCreator_h */
