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
#include "L3DMesh.h"
#include "LInterface.h"
#include <vector>

typedef struct GLInt3
{
    GLuint x;
    GLuint y;
    GLuint z;
} GLInt3;

enum VERTEX_TYPE
{
    VERTEX_TYPE_POSITION = 1,
    VERTEX_TYPE_NORMAL = 1 << 1,
    VERTEX_TYPE_DEFFUSE = 1 << 2,
    VERTEX_TYPE_TEXTURE = 1 << 3,
};

class LMeshCreator
{
public:
    LMeshCreator();
    ~LMeshCreator();
    
    bool Init();
    bool Create(const char* cszFileName);

    bool AddVerties(float* pVerties, GLuint uType, GLuint nCount = 1);
    bool AddFaces(GLInt3* pFaces, GLuint nCount = 1);
    
private:
    
    std::vector<glm::vec3> m_Verties;
    std::vector<glm::vec3> m_Normals;
    std::vector<GLCOLOR> m_Diffuses;
    std::vector<glm::vec3> m_Textures;
    std::vector<GLInt3> m_Faces;
};

#endif /* LMeshCreator_h */
