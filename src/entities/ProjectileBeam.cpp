#include "entities\ProjectileBeam.h"
#include "math.h"

#include "iostream"
using namespace std;

ProjectileBeam::ProjectileBeam( TowerFramework* tower, IAttack* attack ) : IProjectile( tower, attack ) {
    m_box.w = 2;

    m_box.x = tower->getBodyBox()->x + tower->getBodyBox()->w / 2;
    m_box.y = tower->getBodyBox()->y + tower->getBodyBox()->h / 2;

    m_xPosition = m_box.x;
    m_yPosition = m_box.y;

    m_lightBox.x = m_box.x;
    m_lightBox.y = m_box.y;
    m_lightBox.w = m_box.w * 3;
    m_lightBox.h = m_box.h;

    m_headBox.w = 7;
    m_headBox.h = 7;
}

void ProjectileBeam::update( Engine* game, float timeStep ) {
    m_angle = game->calcAngle( m_box.x, m_enemy->getBox()->x + m_enemy->getBox()->w / 2,
                               m_box.y, m_enemy->getBox()->y + m_enemy->getBox()->h / 2 );

    m_distance = game->calcDistance( m_box.x, m_enemy->getBox()->x + m_enemy->getBox()->w / 2,
                                     m_box.y, m_enemy->getBox()->y + m_enemy->getBox()->h / 2 );

    float px = m_tower->getBodyBox()->x + m_tower->getBodyBox()->w / 2;
    float py = m_tower->getBodyBox()->y + m_tower->getBodyBox()->h / 2;

    float x1 = m_box.x + m_distance / 2 + m_tower->getCannonBox()->h * 0.22;
    float y1 = m_box.y;

    float newX = px + ( x1 - px ) * cos( m_angle ) - ( y1 - py ) * sin( m_angle );
    float newY = py + ( x1 - px ) * sin( m_angle ) + ( y1 - py ) * cos( m_angle );

    m_xPosition = (int)newX;
    m_yPosition = (int)newY;

    m_angle = game->calcRadianToDegree( m_angle );

    m_box.h = (int)m_distance - m_tower->getCannonBox()->h * 0.44;

    m_lightBox.x = m_box.x;
    m_lightBox.y = m_box.y;
    m_lightBox.h = m_box.h;

    if( m_tower->canFire() ) {
        m_enemy->dealDamage( m_towerDamage );
    }
}

void ProjectileBeam::render( Engine* game ) {
    game->drawTexture( "PROJECTILE_BEAM_BODY", m_xPosition, m_yPosition, NULL, &m_box, true, true, m_angle + 90 );
    game->drawTexture( "UTIL_BEAM_RED_LIGHT",  m_xPosition, m_yPosition, NULL, &m_lightBox, true, true, m_angle + 90 );
    game->drawTexture( "PROJECTILE_BEAM_HEAD", m_enemy->getBox()->x + m_enemy->getBox()->w / 2, m_enemy->getBox()->y + m_enemy->getBox()->h / 2, NULL, &m_headBox, true, true);
}
