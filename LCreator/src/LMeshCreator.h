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
    unsigned int x;
    unsigned int y;
    unsigned int z;
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
    GLVec3 Vertex;
    union
    {
        GLVec3 Normal;
        GLVec3 Diffuse;
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

    bool AddVerties(GLVec3* pVerties, unsigned int nCount = 1);
    bool AddDiffuseVerties(GL_VERTEX* pVerties, unsigned int nCount = 1);
    bool AddFaces(GLInt3* pFaces, unsigned int nCount = 1);
    
private:
    std::vector<GLVec3> m_Verties;
    std::vector<GLVec3> m_Normals;
    std::vector<GLCOLOR> m_Diffuses;
    std::vector<GLUVW3> m_Textures;
    std::vector<GLInt3> m_Faces;
};

#endif /* LMeshCreator_h */
