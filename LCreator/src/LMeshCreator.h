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

    bool AddVerties(GLVec3* pVerties, unsigned int nCount = 1);
    bool AddFaces(GLFace3* pFaces, unsigned int nCount = 1);
    bool AddNomals(GLVec3* pNomals, unsigned int nCount = 1);
    bool AddTextures(GLTEX2* pNomals, unsigned int nCount = 1);
    
private:
    std::vector<GLVec3> m_Verties;
    std::vector<GLFace3> m_Faces;
    std::vector<GLVec3> m_Normals;
    std::vector<GLTEX2> m_Textures;
};

#endif /* LMeshCreator_h */
