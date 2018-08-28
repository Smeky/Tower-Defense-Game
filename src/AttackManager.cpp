#include "AttackManager.h"

IAttack* AttackManager::getAttack( std::string abilityName ) {
         if( abilityName == "no_ability" )  return new IAttack();
    else if( abilityName == "slow" )        return new AttackSlow();
    else if( abilityName == "freeze" )      return new AttackFreeze();
    else if( abilityName == "blast" )       return new AttackBlast();
    else return new IAttack();
}
