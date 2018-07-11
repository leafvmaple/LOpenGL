#include "L3DShader.h"
#include "LInterface.h"
#include "io/LFileReader.h"

L3DShader::L3DShader()
: m_nShaderProgram(0)
{
    
}

L3DShader::~L3DShader()
{
    Uninit();
}

void L3DShader::Uninit()
{
    
}

bool L3DShader::LoadShader(const char* pVertexPath, const char* pFragmentPath)
{
    int nRetCode = 0;
    bool bResult = false;
    
    do
    {
        int nVertexShader = 0;
        nRetCode = CreateShader(pVertexPath, GL_VERTEX_SHADER, &nVertexShader);
        BOOL_ERROR_BREAK(nRetCode);

        int nFragmentShader = 0;
        nRetCode = CreateShader(pFragmentPath, GL_FRAGMENT_SHADER, &nFragmentShader);
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

bool L3DShader::UpdateShader() const
{
    glUseProgram(m_nShaderProgram);
    return true;
}

bool L3DShader::CreateShader(const char* pShaderPath, int nShaderType, int* pShaderID)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        size_t uBuffLen = 0;
        unsigned char* pBuff = new unsigned char[FILE_BUFF_LEN];
        bRetCode = LFileReader::Reader(pShaderPath, &pBuff, &uBuffLen);
        BOOL_ERROR_BREAK(bRetCode);
        
        pBuff[uBuffLen] = '\0';
        const char* pShaderCode = (const char*)pBuff;

        int nShaderID = glCreateShader(nShaderType);
        glShaderSource(nShaderID, 1, &pShaderCode, NULL);
        glCompileShader(nShaderID);

        bRetCode = CheckCompileErrors(nShaderID, nShaderType);
        BOOL_ERROR_BREAK(bRetCode);

        *pShaderID = nShaderID;

        bResult = true;
    } while (0);

    return bResult;
}

void L3DShader::SetBool(const char* szValueName, bool value) const
{         
    glUniform1i(glGetUniformLocation(m_nShaderProgram, szValueName), (int)value); 
}

void L3DShader::SetInt(const char* szValueName, int value) const
{ 
    glUniform1i(glGetUniformLocation(m_nShaderProgram, szValueName), value); 
}

void L3DShader::SetFloat(const char* szValueName, float value) const
{ 
    glUniform1f(glGetUniformLocation(m_nShaderProgram, szValueName), value); 
}

void L3DShader::SetMatrix(const char *szValueName, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_nShaderProgram, szValueName),
                       1, GL_FALSE, glm::value_ptr(value));
}

bool L3DShader::CheckCompileErrors(GLuint nShader, int nShaderType)
{
    bool bResult = false;
    int nRetCode = 0;

    do 
    {
        glGetShaderiv(nShader, GL_COMPILE_STATUS, &nRetCode);
        BOOL_ERROR_BREAK(nRetCode);

        bResult = true;
    } while (0);

    return bResult;
}
