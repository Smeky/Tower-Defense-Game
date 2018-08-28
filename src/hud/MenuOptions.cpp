#include "MenuOptions.h"
#include "MenuState.h"
#include "ButtonMenuPage.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> _Buttons;

enum PAGE_ID {
    PAGE_VIDEO = 1,
    PAGE_AUDIO,
};

enum BUTTON_ID {
    BUTTON_VIDEO = 1,
    BUTTON_AUDIO,
    BUTTON_BACK
};

void MenuOptions::init( Engine* game ) {
    m_bgBox.w = 620;
    m_bgBox.h = 450;
    m_bgBox.x = ( game->getWindowW() - m_bgBox.w ) / 2 + 25;
    m_bgBox.y = ( game->getWindowH() - m_bgBox.h ) / 2;

    m_currPage  = PAGE_VIDEO;

    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_MAP",       { m_bgBox.x - 50, m_bgBox.y + 51 * 0, 50, 50 }, BUTTON_VIDEO ) );
    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_TALENTS",   { m_bgBox.x - 50, m_bgBox.y + 51 * 1, 50, 50 }, BUTTON_AUDIO ) );
    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_MENU",      { m_bgBox.x - 50, m_bgBox.y + m_bgBox.h - 50, 50, 50 }, BUTTON_BACK ) );

    m_pgVideo.init( game, m_bgBox );
    m_pgAudio.init( game, m_bgBox );
}

void MenuOptions::close() {
    while( !m_pgButtons.empty() ) delete m_pgButtons.back(), m_pgButtons.pop_back();

    m_pgVideo.close();
    m_pgAudio.close();
}

void MenuOptions::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    for( _Buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }

    switch( m_currPage ) {
    case PAGE_VIDEO: m_pgVideo.handleEvents( game, event, mousePos ); break;
    case PAGE_AUDIO: m_pgAudio.handleEvents( game, event, mousePos ); break;
    }
}

void MenuOptions::update( Engine* game, MenuState* state, float timeStep ) {
    for( _Buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, state, (*it)->getID() );
        }

        if( m_currPage == (*it)->getID() ) {
            (*it)->setSelect( true );
        }
        else {
            (*it)->setSelect( false );
        }

        (*it)->update( game, timeStep );

    }

    switch( m_currPage ) {
    case PAGE_VIDEO: m_pgVideo.update( game, timeStep ); break;
    case PAGE_AUDIO: m_pgAudio.update( game, timeStep ); break;
    }
}

void MenuOptions::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_bgBox );

    for( _Buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        (*it)->render( game );
    }

    switch( m_currPage ) {
    case PAGE_VIDEO: m_pgVideo.render( game ); break;
    case PAGE_AUDIO: m_pgAudio.render( game ); break;
    }
}

void MenuOptions::handleClick( Engine* game, MenuState* state, int id ) {
    switch( id ) {
    case BUTTON_VIDEO: m_currPage = PAGE_VIDEO; break;
    case BUTTON_AUDIO: m_currPage = PAGE_AUDIO; break;
    case BUTTON_BACK: state->changeMenuState( MENU_MAIN ); break;
    }

    game->playSound( "UI_BUTTON_PRESS" );
}
