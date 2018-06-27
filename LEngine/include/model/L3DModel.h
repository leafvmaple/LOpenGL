
#ifndef _LMODEL_H_
#define _LMODEL_H_

#include "LInterface.h"

class L3DModel : public ILModel
{
public:
    L3DModel();
    ~L3DModel();

    bool Init(const void* pModelVertices,
              GLsizeiptr nVerticesCount,
              const void* pModelIndices,
              GLsizeiptr nIndicesCount,
              const char *pVertexShaderSource,
              const char *pFragmentShaderSource);

    bool InitVertex(const void* pModelVertices,
                    GLsizeiptr nVerteicesCount,
                    const void* pModelIndices,
                    GLsizeiptr nIndicesCount);

    bool InitShader(const char *pVertexShaderSource,
                    const char *pFragmentShaderSource);

public:
    bool UpdateDisplay();

private:
    unsigned int m_nVertexArrObj;
    unsigned int m_nVertexBufObj;
    unsigned int m_nElemBufObj;

    unsigned int m_nShaderProgram;
};

#endif
