#include "entities/IProjectile.h"
#include "math.h"

#include "iostream"
using namespace std;

IProjectile::IProjectile( Projectile_data data, TowerFramework* turret, IAttack* attack ) {
    m_data      = data;
    m_attack    = attack;
    m_turret    = turret;
    m_enemy     = turret->getEnemy();
    m_destBox   = *m_enemy->getBox();

    SDL_Rect* turretBox = turret->getBodyBox();

    m_xPos = turretBox->x + turretBox->w / 2;
    m_yPos = turretBox->y + turretBox->h / 2;

    m_box.x = (int)m_xPos;
    m_box.y = (int)m_yPos;
    m_box.w = m_data.width;
    m_box.h = m_data.height;

    m_despawn   = false;
    m_velFixed  = false;
    m_enemyDied = false;
    m_angle     = 0;
    m_fixedVel  = m_data.vel;
}

IProjectile::~IProjectile() {
    m_attack    = NULL;
    m_turret    = NULL;
    m_enemy     = NULL;
}

void IProjectile::update( Engine* game, float timeStep ) {
    if( !m_velFixed ) {
        m_fixedVel = m_fixedVel * ( (float)game->getWindowW() / game->getWindowBaseW() );
        m_velFixed = true;
    }

    if( game->checkCollision( m_box, m_destBox ) ) {
        if( !m_enemyDied ) {
            m_attack->doAttack( m_turret );
        }

        m_despawn = true;
    }
    else {
        if( m_enemy->isDead() ) {
            m_enemyDied = true;
        }

        if( !m_enemyDied ) {
            m_destBox = *m_enemy->getBox();
        }

        m_angle = game->calcAngle( m_box.x + m_box.w / 2, m_destBox.x + m_destBox.w / 2,
                                   m_box.y + m_box.h / 2, m_destBox.y + m_destBox.h / 2 );


        // Velocity of movement
        float speed = timeStep * m_fixedVel;

        // Calculate new position
        m_xPos += speed * (float)cos( m_angle );
        m_yPos += speed * (float)sin( m_angle );

        m_angle = game->calcRadianToDegree( m_angle );

        // Stores position in rectangle -> used for drawing, etc.
        m_box.x = (int)m_xPos;
        m_box.y = (int)m_yPos;
    }
}

void IProjectile::render( Engine* game ) {
    game->drawTexture( m_data.tex, m_box.x, m_box.y, NULL, &m_box, true, true, m_angle + 90 );
}
