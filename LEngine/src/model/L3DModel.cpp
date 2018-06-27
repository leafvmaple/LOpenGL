#include "model\L3DModel.h"
#include "Linterface.h"

L3DModel::L3DModel()
: m_nVertexArrObj(0)
, m_nVertexBufObj(0)
, m_nElemBufObj(0)
, m_nShaderProgram(0)
{
}


L3DModel::~L3DModel()
{
    m_nVertexArrObj = 0;
    m_nVertexBufObj = 0;
    m_nElemBufObj = 0;
}

bool L3DModel::Init(const void* pModelVerteices,
                    GLsizeiptr nVerticesCount,
                    const void* pModelIndices,
                    GLsizeiptr nIndicesCount,
                    const char *pVertexShaderSource,
                    const char *pFragmentShaderSource)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        bRetCode = InitVertex(pModelVerteices, nVerticesCount, pModelIndices, nIndicesCount);
        BOOL_ERROR_BREAK(bRetCode);

        bRetCode = InitShader(pVertexShaderSource, pFragmentShaderSource);
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
}

bool L3DModel::InitVertex(const void* pModelVertices,
                          GLsizeiptr nVerticesCount,
                          const void* pModelIndices,
                          GLsizeiptr nIndicesCount)
{
    bool bResult = false;

    do 
    {
        glGenVertexArrays(1, &m_nVertexArrObj);
        glGenBuffers(1, &m_nVertexBufObj);
        glGenBuffers(1, &m_nElemBufObj);

        glBindVertexArray(m_nVertexArrObj);

        glBindBuffer(GL_ARRAY_BUFFER, m_nVertexBufObj);
        glBufferData(GL_ARRAY_BUFFER, nVerticesCount, pModelVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElemBufObj);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndicesCount, pModelIndices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);

        bResult = true;
    } while (0);

    return bResult;
}

bool L3DModel::InitShader(const char *pVertexShaderSource,
                          const char *pFragmentShaderSource)
{
    bool bResult = false;
    int nRetCode = 0;

    do 
    {
        int nVertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(nVertexShader, 1, &pVertexShaderSource, NULL);
        glCompileShader(nVertexShader);
        glGetShaderiv(nVertexShader, GL_COMPILE_STATUS, &nRetCode);
        BOOL_ERROR_BREAK(nRetCode);

        int nFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(nFragmentShader, 1, &pFragmentShaderSource, NULL);
        glCompileShader(nFragmentShader);
        glGetShaderiv(nFragmentShader, GL_COMPILE_STATUS, &nRetCode);
        BOOL_ERROR_BREAK(nRetCode);

        m_nShaderProgram = glCreateProgram();
        glAttachShader(m_nShaderProgram, nVertexShader);
        glAttachShader(m_nShaderProgram, nFragmentShader);
        glLinkProgram(m_nShaderProgram);
        glGetProgramiv(m_nShaderProgram, GL_LINK_STATUS, &nRetCode);
        BOOL_ERROR_BREAK(nRetCode);

        glDeleteShader(nVertexShader);
        glDeleteShader(nFragmentShader);

        bResult = true;
    } while (0);

    return bResult;
}

bool L3DModel::UpdateDisplay()
{
    bool bResult = false;

    do 
    {
        glUseProgram(m_nShaderProgram);
        glBindVertexArray(m_nVertexArrObj);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        bResult = true;
    } while (0);

    return bResult;
}
