#include "LAssert.h"

#include "object/LCharacter.h"

LCharacter::LCharacter()
{

}

bool LCharacter::Create(IL3DEngine* p3DEngine)
{
    bool bResult = false;
    bool bRetCode = false;

    do 
    {
        float pVertices[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        unsigned int pIndices[] = {
            0, 1, 3,
            1, 2, 3
        };

        const char *pVertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        const char *pFragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        bRetCode = ILModel::Create(IL3DEngine::Instance(),
                                    pVertices,
                                    sizeof(pVertices),
                                    pIndices,
                                    sizeof(pIndices),
                                    pVertexShaderSource,
                                    pFragmentShaderSource,
                                    &m_pObject);
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
}
