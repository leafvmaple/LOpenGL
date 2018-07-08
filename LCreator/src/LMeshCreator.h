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

typedef struct GLUVW3
{
    GLuint u;
    GLuint v;
    GLuint w;
    GLUVW3(GLuint u, GLuint v, GLuint w) : u(u), v(v), w(w) {}
} GLUVW3;

typedef struct GLUV2
{
    GLuint u;
    GLuint v;
    
    operator GLUVW3() {return GLUVW3(u, v, 0);}
} GLUV2;

typedef struct GL_VERTEX
{
    glm::vec3 Vertex;
    union
    {
        glm::vec3 Normal;
        glm::vec3 Diffuse;
    };
    GLUV2 Texture;
} GL_VERTEX;

class LMeshCreator
{
public:
    LMeshCreator();
    ~LMeshCreator();
    
    bool Init();
    bool Create(const char* cszFileName);

    bool AddVerties(glm::vec3* pVerties, GLuint nCount = 1);
    bool AddDiffuseVerties(GL_VERTEX* pVerties, GLuint nCount = 1);
    bool AddFaces(GLInt3* pFaces, GLuint nCount = 1);
    
private:
    std::vector<glm::vec3> m_Verties;
    std::vector<glm::vec3> m_Normals;
    std::vector<GLCOLOR> m_Diffuses;
    std::vector<GLUVW3> m_Textures;
    std::vector<GLInt3> m_Faces;
};

#endif /* LMeshCreator_h */
