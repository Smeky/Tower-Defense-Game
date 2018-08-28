#ifndef ATTACKMANAGER_H
#define ATTACKMANAGER_H

#include "IAttack.h"

class AttackManager {
public:
    IAttack* getAttack( std::string abilityName );
};

#endif // ATTACKMANAGER_H
