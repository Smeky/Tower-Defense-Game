#include "hud\TrackerHealth.h"

void TrackerHealth::init( Engine* game, int startHealth ) {
    m_health = startHealth;
    m_startHealth = startHealth;

    m_text.loadFromText( game->intToString( m_health ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

    update( game );
}

void TrackerHealth::add( Engine* game, int amount ) {
    m_health += amount;

    update( game );
}

bool TrackerHealth::remove( Engine* game, int amount ) {
    m_health -= amount;

    if( ( m_health ) <= 0 ) {
        update( game );

        m_health = 0;

        return false;
    }
    else {
        update( game );

        return true;
    }
}

void TrackerHealth::reset( Engine* game ) {
    m_health = m_startHealth;
    update( game );
}

void TrackerHealth::render( Engine* game, int x, int y ) {
    m_text.loadFromText( game->intToString( m_health ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    game->drawTexture( "UTIL_HEARTH", x, y, NULL, NULL, false, true );
    m_text.render( x + 17, y, game->getRenderer(), NULL, NULL, false, true );
}

void TrackerHealth::update( Engine* game ) {
}
