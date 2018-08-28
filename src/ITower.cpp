#include "ITower.h"
#include "math.h"

#include "iostream"
using namespace std;

ITower::ITower( SDL_Rect box, int type ) {
    m_box           = box;
    m_type          = type;

    m_targetLocked          = false;
    m_cannonAngle           = 0.0;
    m_fireCooldownProgress  = 0.0;
    m_blastDamage           = 0;

    m_sell      = false;
    m_upgrade   = false;
}

void ITower::setFireCooldown( float timeStep ) {
    m_fireCooldownProgress += m_fireVelocity * timeStep;

    if( m_fireCooldownProgress > m_fireCooldown ) {
        m_canFire = true;
    }
    else m_canFire = false;
}

void ITower::lockTarget( IEnemy* enemy ) {
    m_enemy = enemy;

    m_targetLocked = true;
}

void ITower::freeTarget() {
    m_enemy = NULL;
    m_targetLocked = false;
}

bool ITower::canFire( Engine* game ) {
    bool didFire = false;

    if( m_enemy != NULL ) {
        if( !m_enemy->isDead() ) {
            if( isInDistance( game ) ) {
                setCannonAngle( game );

                if( m_canFire ) {
                    didFire = true;

                    fired();
                }
            }
            else freeTarget();
        }
        else freeTarget();
    }

    return didFire;
}

void ITower::setCannonAngle( Engine* game ) {
    if( m_enemy != NULL ) {
        m_cannonAngle = game->calcAngle( m_box.x + m_box.w / 2, m_enemy->getBox()->x + m_enemy->getBox()->w / 2,
                                         m_box.y + m_box.h / 2, m_enemy->getBox()->y + m_enemy->getBox()->h / 2 );

        float px = m_box.x + m_box.w / 2;
        float py = m_box.y + m_box.h / 2;

        float x1 = m_box.x + m_box.w / 2 + m_cannonBox.w / 3;
        float y1 = m_box.y + m_box.h / 2;

        float newX = px + ( x1 - px ) * cos( m_cannonAngle ) - ( y1 - py ) * sin( m_cannonAngle );
        float newY = py + ( x1 - px ) * sin( m_cannonAngle ) + ( y1 - py ) * cos( m_cannonAngle );

        m_cannonBox.x = (int)newX;
        m_cannonBox.y = (int)newY;

        m_cannonAngle = game->calcRadianToDegree( m_cannonAngle );
    }
}

void ITower::setUpgrade( int type ) {
    m_upgradeType = type;
    m_upgrade     = true;
}

void ITower::resetUpgrade() {
    m_upgradeType = 0;
    m_upgrade     = false;
}

bool ITower::isInDistance( Engine* game ) {
    if( game->calcDistance( m_box.x + m_box.w / 2, m_enemy->getBox()->x + m_enemy->getBox()->w / 2,
                            m_box.y + m_box.h / 2, m_enemy->getBox()->y + m_enemy->getBox()->h / 2 ) < m_fireRadius ) {

        return true;
    }

    return false;
}

void ITower::render( Engine* game ) {
    game->drawTexture( m_text,  m_box.x, m_box.y, NULL, &m_box );
    game->drawTexture( m_cannonText, m_cannonBox.x, m_cannonBox.y, NULL, &m_cannonBox, true, true, m_cannonAngle + 90 );
}
