#ifndef ATTACKSLOW_H
#define ATTACKSLOW_H

#include "IAttack.h"

class AttackSlow : public IAttack {
public:
    bool doAttack( TowerFramework* turret ) {
        IAttack::doAttack( turret );

        turret->getEnemy()->slow( 20, 50 );
    }
};

#endif // ATTACKSLOW_H
