#include "ExpManager.h"
#include "math.h"

#include "iostream"
using namespace std;

void ExpManager::init( Engine* game, SDL_Rect box ) {
    m_barBox.w = box.w * 0.5;
    m_barBox.h = 25;
    m_barBox.x = box.x + ( box.w - m_barBox.w ) / 2;
    m_barBox.y = box.y + 20;

    m_progBox.x = m_barBox.x + 1;
    m_progBox.y = m_barBox.y + 1;
    m_progBox.w = m_barBox.w - 2;
    m_progBox.h = m_barBox.h - 2;

    m_plv = game->Saves()->m_pLv;
    m_exp = game->Saves()->m_exp;

    m_maxXp = 100 * pow( m_plv, 1.2 );

    m_textLevel.loadFromText( game->intToString( m_plv ),   game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    m_textCurXP.loadFromText( game->intToString( m_exp ),   game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    m_textMaxXP.loadFromText( game->intToString( m_maxXp ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    m_textSlash.loadFromText( "/",                          game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
    m_textLvShort.loadFromText( "Lv.",                      game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

    m_progBox.w = ( (float)m_barBox.w / 100 ) * ( m_exp / ( (float)m_maxXp / 100 ) );
}

void ExpManager::update( Engine* game, float timeStep ) {
    bool updateExp = false;
    while( m_exp >= m_maxXp ) {
        updateExp = true;

        m_plv += 1;
        m_exp -= m_maxXp;

        m_maxXp = 100 * pow( m_plv, 1.2 );
    }

    if( updateExp ) {
        game->Saves()->m_pLv = m_plv;
        game->Saves()->m_exp = m_exp;
        game->Saves()->saveGame();

        m_textLevel.loadFromText( game->intToString( m_plv ),   game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
        m_textCurXP.loadFromText( game->intToString( m_exp ),   game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
        m_textMaxXP.loadFromText( game->intToString( m_maxXp ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );

        m_progBox.w = ( (float)m_barBox.w / 100 ) * ( m_exp / ( (float)m_maxXp / 100 ) );
    }
}

void ExpManager::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 40, 40, 40, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_barBox );

    SDL_SetRenderDrawColor( game->getRenderer(), 0, 0, 0, 255 );
    SDL_RenderDrawRect( game->getRenderer(), &m_barBox );

    SDL_SetRenderDrawColor( game->getRenderer(), 70, 70, 70, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_progBox );

    m_textLvShort.render( m_barBox.x + 10,
                        m_barBox.y + m_barBox.h / 2 + 1,
                        game->getRenderer(), NULL, NULL, false, true );

    m_textLevel.render( m_barBox.x + 35,
                        m_barBox.y + m_barBox.h / 2 + 1,
                        game->getRenderer(), NULL, NULL, false, true );

    m_textCurXP.render( m_barBox.x + m_barBox.w / 2 - ( m_textCurXP.getWidth() / 2 + 10 ),
                        m_barBox.y + m_barBox.h / 2 + 1,
                        game->getRenderer(), NULL, NULL, true, true );

    m_textSlash.render( m_barBox.x + m_barBox.w / 2,
                        m_barBox.y + m_barBox.h / 2 + 1,
                        game->getRenderer(), NULL, NULL, true, true );

    m_textMaxXP.render( m_barBox.x + m_barBox.w / 2 + 10,
                        m_barBox.y + m_barBox.h / 2 + 1,
                        game->getRenderer(), NULL, NULL, false, true );
}

void ExpManager::addExp( int amount ) {
    m_exp += amount;
}
