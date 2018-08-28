#include "FireEffect.h"

FireEffect::FireEffect( Engine* game, std::string texture, int x, int y, int w, int h ) {
    m_texture   = texture;
    m_box       = { x, y, game->calcByResW( w ), game->calcByResH( h ) };

    m_alpha = 255;
}

void FireEffect::update( Engine* game, float timeStep ) {


    if( m_alphaEnabled ) {
        game->setTextureAlpha( m_texture, m_alpha );
    }
}

void FireEffect::render( Engine* game ) {
    if( m_timeProgress < m_displayTime ) {
        game->drawTexture( m_texture, m_box.x, m_box.y, NULL, &m_box );
    }
}

void FireEffect::enableAlpha( int velocity, float time ) {
    m_alphaEnabled  = true;
    m_alphaVelocity = velocity;
}

void FireEffect::disableAlpha() {
    m_alphaEnabled = false;
}

void FireEffect::setAlphaVel( int velocity ) {
    m_alphaVelocity = velocity;
}

void FireEffect::setTimer( float time ) {
    m_displayTime = time;
}

void FireEffect::reset() {
    m_alpha = 255;
}
