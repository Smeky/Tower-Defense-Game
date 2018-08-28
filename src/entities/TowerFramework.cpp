#include "entities/TowerFramework.h"
#include "IAttack.h"
#include "math.h"

#include "iostream"
using namespace std;

TowerFramework::TowerFramework( Engine* game, Tower_data data, SDL_Rect box, int blockID ) {
    m_data      = data;
    m_blockID   = blockID;
    m_bodyBox   = box;

    m_data.range = game->calcByResW( m_data.range );

    m_cannon                = new TurretCannon( game, m_data.tex_cannon, m_bodyBox );
    m_enemy                 = NULL;
    m_fireCooldown          = 10.0;
    m_fireCooldownProgress  = 10.0;
    m_targetLocked          = false;
    m_canFire               = true;
    m_isSold                = false;
    m_isUpgrade             = false;
    m_hasProject            = m_data.projectName != "no_projectile";
}

TowerFramework::~TowerFramework() {
    m_enemy     = NULL;
    m_attack    = NULL;
    delete m_cannon;
}

void TowerFramework::update( Engine* game, float timeStep ) {
    m_fireCooldownProgress += m_data.atts * timeStep;
    m_canFire = false;

    if( m_enemy != NULL ) {
        if( m_enemy->isDead() ) {
            freeTarget();
        }
        else {
            if( game->calcDistance( m_bodyBox.x + m_bodyBox.w / 2, m_enemy->getBox()->x + m_enemy->getBox()->w / 2,
                                    m_bodyBox.y + m_bodyBox.h / 2, m_enemy->getBox()->y + m_enemy->getBox()->h / 2 ) > m_data.range ) {

                freeTarget();
            }
            else {
                m_cannon->update( game, m_bodyBox, *m_enemy->getBox() );

                if( m_fireCooldown < m_fireCooldownProgress ) {
                    m_canFire = true;
                    m_fireCooldownProgress  = 0.0;

                    if( !m_hasProject ) {
                        m_attack->doAttack( this );
                    }
                }
            }
        }
    }
}

void TowerFramework::render( Engine* game ) {
    game->drawTexture( m_data.tex_body, m_bodyBox.x, m_bodyBox.y, NULL, &m_bodyBox );
}

void TowerFramework::renderCannon( Engine* game ) {
    m_cannon->render( game );
}

void TowerFramework::findTarget( Engine* game, std::vector<IEnemy*> &enemies ) {
    int enemyIndex      = -1;
    float enemyTravel   = 0;

    for( int i = 0; i < (int)enemies.size(); i++ ) {
        float enemyDistance = game->calcDistance( m_bodyBox.x + m_bodyBox.w / 2, enemies[ i ]->getBox()->x + enemies[ i ]->getBox()->w / 2,
                                                  m_bodyBox.y + m_bodyBox.h / 2, enemies[ i ]->getBox()->y + enemies[ i ]->getBox()->h / 2 );

        if( enemyDistance < m_data.range ) {
            if( enemies[ i ]->getTravelDistance() > enemyTravel ) {
                enemyTravel = enemies[ i ]->getTravelDistance();
                enemyIndex = i;
            }
        }
    }

    if( enemyIndex != -1 ) {
        lockTarget( enemies[ enemyIndex ] );
    }
}

void TowerFramework::lockTarget( IEnemy* enemy ) {
    m_enemy         = enemy;
    m_targetLocked  = true;
}

void TowerFramework::freeTarget() {
    m_enemy         = NULL;
    m_targetLocked  = false;
}

void TowerFramework::upgradeTower( Tower_data data ) {
    m_isUpgrade     = true;
    m_upgradeData   = data;
}

void TowerFramework::finishUpgrade( Engine* game ) {
    m_isUpgrade = false;
    m_data      = m_upgradeData;

    m_data.range = game->calcByResW( m_data.range );
}
