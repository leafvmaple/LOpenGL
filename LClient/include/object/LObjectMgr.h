#ifndef _LOBJECTMGR_H_
#define _LOBJECTMGR_H_

#include "LInterface.h"

#ifdef WIN32
#include <list>
#endif

class LModel;

class LObjectMgr
{
public:
    LObjectMgr();
    ~LObjectMgr();

    void Uninit();

    template<typename T>
    T* CreateModel(const char* pwcsMeshPath)
    {
        T* pObject = NULL;
        pObject = new T(pwcsMeshPath);
        m_ObjectList.push_back(pObject);
        pObject->Create(IL3DEngine::Instance());
        return pObject;
    }

    template<typename T>
    T* CreateModel()
    {
        T* pObject = NULL;
        pObject = new T;
        m_ObjectList.push_back(pObject);
        pObject->Create(IL3DEngine::Instance());
        return pObject;
    }

    bool Update(float fDeltaTime);

    bool IsActive();

private:
    std::list<LModel*> m_ObjectList;
};

#endif