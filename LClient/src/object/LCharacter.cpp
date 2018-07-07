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
        bRetCode = ILModel::Create(IL3DEngine::Instance(), "res/model/Rect.mesh", &m_pObject);

        /*bRetCode = ILModel::Create(IL3DEngine::Instance(),
                                    pVertices,
                                    sizeof(pVertices),
                                    pIndices,
                                    sizeof(pIndices),
                                    "res/shader/vertex.vs",
                                    "res/shader/fragment.fs",
                                    &m_pObject);*/
        BOOL_ERROR_BREAK(bRetCode);

        bResult = true;
    } while (0);

    return bResult;
}
