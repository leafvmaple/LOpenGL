#include "LAssert.h"

#include "LCharacter.h"

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

        bRetCode = ILModel::Create(IL3DEngine::Instance(),
                                    pVertices,
                                    sizeof(pVertices),
                                    pIndices,
                                    sizeof(pIndices),
                                    "res/shader/vertex.vs",
                                    "res/shader/fragment.fs",
                                    &m_pObject);
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
}
