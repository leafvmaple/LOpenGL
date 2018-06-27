#ifndef _LSHADER_H_
#define _LSHADER_H_

#define FILE_BUFF_LEN 4096

class L3DShader
{
public:
    L3DShader();
    ~L3DShader();

    bool Init(const char* pVertexPath, const char* pFragmentPath);
    void Uninit();

    void User() const;
    void L3DShader::setBool(const char* szValueName, bool value) const;
    void L3DShader::setInt(const char* szValueName, int value) const;
    void L3DShader::setFloat(const char* szValueName, float value) const;

private:
    bool CreateShader(const char* pShaderPath, int ShaderType, int* pShaderID);
    bool CheckCompileErrors(unsigned int nShader, int nShaderType);

    int m_nShaderProgram;
};

#endif
