#include "hud\GameoverMenu.h"
#include "hud\ButtonMenu.h"
#include "MenuState.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> Button;

enum BUTTON_ID {
    BUTTON_ID_RESTART,
    BUTTON_ID_EXIT
};

void GameoverMenu::init( Engine* game ) {
    m_bgBox.x = 0;
    m_bgBox.y = 0;
    m_bgBox.w = game->getWindowW();
    m_bgBox.h = game->getWindowH();

    m_inBox.w = m_bgBox.w / 2;
    m_inBox.h = m_bgBox.h / 3;
    m_inBox.x = m_bgBox.x + ( m_bgBox.w - m_inBox.w ) / 2;
    m_inBox.y = m_bgBox.y + m_bgBox.h / 4;

    m_gameoverBox.w = 390;
    m_gameoverBox.h = 50;
    m_gameoverBox.x = m_inBox.x + ( m_inBox.w - m_gameoverBox.w ) / 2;
    m_gameoverBox.y = m_inBox.y + 20;

    m_stateChange = false;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RESTART", m_gameoverBox.x + 30,                    m_inBox.y + m_inBox.h - 40, 120, 20, BUTTON_ID_RESTART ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_MAINMENU",m_gameoverBox.x + m_gameoverBox.w - 150, m_inBox.y + m_inBox.h - 40, 120, 20, BUTTON_ID_EXIT ) );
}

void GameoverMenu::close() {
    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();
}

void GameoverMenu::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePosition );
    }
}

void GameoverMenu::update( Engine* game, IGameState* state, float timeStep ) {
    if( m_stateChange ) {
        game->changeState( MenuState::instance() );
    }

    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, state, (*it)->getID() );
        }

        (*it)->update( game, timeStep );
    }
}

void GameoverMenu::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 15, 25, 35, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_bgBox );

    SDL_SetRenderDrawColor( game->getRenderer(), 10, 15, 20, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_inBox );

    game->drawTexture( "GAMEOVER", m_gameoverBox.x, m_gameoverBox.y, NULL, &m_gameoverBox );

    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }
}

void GameoverMenu::handleClick( Engine* game, IGameState* state, int id ) {
    switch( id ) {
    case BUTTON_ID_RESTART: state->restart( game ); break;
    case BUTTON_ID_EXIT:    m_stateChange = true; break;
    }
}
