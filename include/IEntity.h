#ifndef IENTITY_H
#define IENTITY_H

#include "core\Engine.h"

class IEntity {
public:
    virtual void render( Engine* game ) = 0;
protected:
    IEntity() {}
};

#endif // IENTITY_H
