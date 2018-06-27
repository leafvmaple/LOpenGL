#ifndef _LMODE_H_
#define _LMODE_H_

#include "LInterface.h"

class L3DENGINE_CLASS ILModel;

class LModel
{
public:
    LModel() { m_pObject = nullptr; };
    ~LModel() {};

protected:
    ILModel* m_pObject;
};

#endif // !_LMODE_H_
