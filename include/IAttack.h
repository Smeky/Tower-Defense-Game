#ifndef IATTACK_H
#define IATTACK_H

#include "math.h"
#include "TowerFramework.h"

class IAttack {
public:
    virtual bool doAttack( TowerFramework* turret ) {
        if( turret->getEnemy() != NULL ) {
            turret->getEnemy()->dealDamage( turret->getDamage() );
            return true;
        }
        else return false;
    }
};

class AttackSlow : public IAttack {
    virtual bool  doAttack( TowerFramework* turret ) {
        if( IAttack::doAttack( turret ) ) {
            turret->getEnemy()->slow( turret->getSlowPwr(), turret->getSlowDur() );
            return true;
        }
        else return false;
    }
};

class AttackFreeze : public IAttack {
    virtual bool  doAttack( TowerFramework* turret ) {
        if( IAttack::doAttack( turret ) ) {
            return true;
        }
        else return false;
    }
};

class AttackBlast : public IAttack {
    virtual bool  doAttack( TowerFramework* turret ) {
        if( IAttack::doAttack( turret ) ) {
            std::vector<IEnemy*> &m_enemies = turret->getEnemies();

            for( int i = 0; i < (int)m_enemies.size(); i++ ) {
                SDL_Rect* hitBox    = turret->getEnemy()->getBox();
                SDL_Rect* enemyBox  = m_enemies[ i ]->getBox();

                float distance = sqrt( pow( ( hitBox->x + hitBox->w / 2 ) - ( enemyBox->x + enemyBox->w / 2 ), 2 ) +
                                       pow( ( hitBox->y + hitBox->h / 2 ) - ( enemyBox->y + enemyBox->h / 2 ), 2 ) );

                if( distance <= turret->getData().blastRange ) {
                    m_enemies[ i ]->dealDamage( turret->getDamage() * turret->getData().blastPwr );
                }
            }

            return true;
        }
        else return false;
    }
};

#endif // IATTACK_H
