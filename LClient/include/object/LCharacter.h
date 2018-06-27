#ifndef _LCHARACTER_H_
#define _LCHARACTER_H_

#include "LModel.h"

class LCharacter : public LModel
{
public:
    LCharacter();
    virtual ~LCharacter() {};

public:
    bool Create(IL3DEngine* p3DEngine);
};

#endif 
