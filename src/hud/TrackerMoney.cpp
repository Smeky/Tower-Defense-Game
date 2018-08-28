#include "hud\TrackerMoney.h"

#include "iostream"
using namespace std;

void TrackerMoney::init( Engine* game, int startMoney ) {
    m_money      = startMoney;
    m_startMoney = startMoney;
    m_maxTextSet = false;

    m_text.loadFromText( game->intToString( m_money ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

    update( game );
}

void TrackerMoney::add( Engine* game, int amount ) {
    m_money += amount;

    if( m_money > 99999 && !m_maxTextSet ) {
        m_text.loadFromText( "99999+", game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

        m_maxTextSet = true;
    }
    else {
        update( game );

        m_maxTextSet = false;
    }
}

bool TrackerMoney::remove( Engine* game, int amount ) {
    m_money -= amount;

    if( ( m_money ) < 0 ) {
        m_money += amount;

        return false;
    }
    else {
        if( m_money > 99999 && !m_maxTextSet ) {
            m_text.loadFromText( "99999+", game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

            m_maxTextSet = true;
        }
        else {
            update( game );

            m_maxTextSet = false;
        }

        return true;
    }
}

void TrackerMoney::reset( Engine* game ) {
    m_money = m_startMoney;
    update( game );
}

void TrackerMoney::render( Engine* game, int x, int y ) {
    m_text.loadFromText( game->intToString( m_money ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    game->drawTexture( "UTIL_COIN",  x,      y, NULL, NULL, false, true );
    m_text.render( x + 17, y, game->getRenderer(), NULL, NULL, false, true );
}

void TrackerMoney::update( Engine* game ) { }
