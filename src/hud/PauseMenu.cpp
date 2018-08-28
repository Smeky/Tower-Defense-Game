#include "hud\PauseMenu.h"

#include "hud\ButtonMenu.h"

#include "MenuState.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> Button;

enum BUTTON_ID {
    BUTTON_ID_RESUME,
    BUTTON_ID_RESTART,
    BUTTON_ID_MAINMENU,
    BUTTON_ID_EXIT,
};

void PauseMenu::init( Engine* game ) {
    m_bgBox.x = 0;
    m_bgBox.y = 0;
    m_bgBox.w = game->getWindowW();
    m_bgBox.h = game->getWindowH();


    m_inBox.w = 244;
    m_inBox.h = 320;
    m_inBox.x = m_bgBox.x + ( m_bgBox.w - m_inBox.w ) / 2;
    m_inBox.y = m_bgBox.y + ( m_bgBox.h - m_inBox.h ) / 2;

    m_stateEnd = false;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RESUME",   m_inBox.x + m_inBox.w / 6, m_inBox.y + m_inBox.h / 8 + ( m_inBox.w / 9 + 5 ) * 0, m_inBox.w / 1.5, m_inBox.w / 9, BUTTON_ID_RESUME,    SDLK_p ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RESTART",  m_inBox.x + m_inBox.w / 6, m_inBox.y + m_inBox.h / 8 + ( m_inBox.w / 9 + 5 ) * 1, m_inBox.w / 1.5, m_inBox.w / 9, BUTTON_ID_RESTART,   SDLK_r ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_MAINMENU", m_inBox.x + m_inBox.w / 6, m_inBox.y + m_inBox.h / 8 + ( m_inBox.w / 9 + 5 ) * 4, m_inBox.w / 1.5, m_inBox.w / 9, BUTTON_ID_MAINMENU ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_EXIT",     m_inBox.x + m_inBox.w / 6, m_inBox.y + m_inBox.h / 8 + ( m_inBox.w / 9 + 5 ) * 7, m_inBox.w / 1.5, m_inBox.w / 9, BUTTON_ID_EXIT ) );
}

void PauseMenu::close() {
    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();
}

void PauseMenu::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePosition );
    }
}

void PauseMenu::update( Engine* game, IGameState* state, float timeStep ) {
    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, state, (*it)->getID() );
        }

        (*it)->update( game, timeStep );
    }

    if( m_stateEnd ) {
        game->changeState( MenuState::instance() );
    }
}

void PauseMenu::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 15, 25, 35, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_bgBox );

    SDL_SetRenderDrawColor( game->getRenderer(), 10, 15, 20, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_inBox );

    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }
}

void PauseMenu::handleClick( Engine* game, IGameState* state, int id ) {
    switch( id ) {
    case BUTTON_ID_RESUME:   state->resume(); break;
    case BUTTON_ID_RESTART:  state->restart( game ); break;
    case BUTTON_ID_MAINMENU: m_stateEnd = true; break;
    case BUTTON_ID_EXIT:     game->setQuit(); break;
    }
}
