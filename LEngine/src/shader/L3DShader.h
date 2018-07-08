#ifndef _LSHADER_H_
#define _LSHADER_H_

#include "LDefine.h"

#define FILE_BUFF_LEN 4096

class L3DShader
{
public:
    L3DShader();
    ~L3DShader();

    
    void Uninit();

    bool LoadShader(const char* pVertexPath, const char* pFragmentPath);
    bool UpdateShader() const;
    
    void setBool(const char* szValueName, bool value) const;
    void setInt(const char* szValueName, int value) const;
    void setFloat(const char* szValueName, float value) const;

private:
    bool CreateShader(const char* pShaderPath, int ShaderType, int* pShaderID);
    bool CheckCompileErrors(GLuint nShader, int nShaderType);

    int m_nShaderProgram;
};

#endif
