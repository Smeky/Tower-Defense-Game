#include "TurretCannon.h"

TurretCannon::TurretCannon( Engine* game, std::string texture, SDL_Rect turretBox ) {
    m_texture = texture;

    m_box.w = game->calcByResW( 20 );
    m_box.h = game->calcByResH( 30 );
    m_box.x = turretBox.x + ( turretBox.w - m_box.w ) / 2;
    m_box.y = turretBox.y + ( turretBox.h - m_box.h ) / 2;

    m_angle = 0.0;
}

void TurretCannon::update( Engine* game, SDL_Rect turretBox, SDL_Rect targetBox ) {
    m_angle = game->calcAngle( turretBox.x + turretBox.w / 2, targetBox.x + targetBox.w / 2,
                               turretBox.y + turretBox.h / 2, targetBox.y + targetBox.h / 2 );

    m_angle = game->calcRadianToDegree( m_angle );
}

void TurretCannon::render( Engine* game ) {
    game->drawTexture( m_texture, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2, NULL, &m_box, true, true, m_angle + 90 );
}
