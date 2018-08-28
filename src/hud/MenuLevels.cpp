#include "hud\MenuLevels.h"

#include "MenuState.h"
#include "hud\ButtonMenu.h"
#include "hud\ButtonLevel.h"

#include "PlayState.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> _button;

enum BUTTON_ID {
    BUTTON_ID_BACK,
    BUTTON_ID_UPGRADES,
    BUTTON_ID_LEVEL_1,
    BUTTON_ID_LEVEL_2,
    BUTTON_ID_LEVEL_3,
};

void MenuLevels::init( Engine* game ) {
    m_stateEnd = false;

    m_backgroundBox.w = 720;
    m_backgroundBox.h = 450;
    m_backgroundBox.x = ( game->getWindowW() - m_backgroundBox.w ) / 2;
    m_backgroundBox.y = ( game->getWindowH() - m_backgroundBox.h ) / 2;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_BACK",     m_backgroundBox.x + 10, m_backgroundBox.y + m_backgroundBox.h - 35, 70, 25, BUTTON_ID_BACK ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_UPGRADES", m_buttons.back()->getBox().x + m_buttons.back()->getBox().w + 5,
                                                                 m_buttons.back()->getBox().y,
                                                                 80, 25, BUTTON_ID_UPGRADES ) );
    m_buttons.push_back( new ButtonLevel( m_backgroundBox.x + 20, m_backgroundBox.y + m_backgroundBox.h / 2, 30, 30, BUTTON_ID_LEVEL_1 ) );
}

void MenuLevels::close() {
    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();
}

void MenuLevels::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePosition );
    }
}

void MenuLevels::update( Engine* game, MenuState* state, float timeStep ) {
    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, state, (*it)->getID() );
        }

        (*it)->update( game, timeStep );
    }

    m_tooltipManager.update( game );

    if( m_stateEnd ) {
        game->playLevel( PlayState::instance(), m_levelPath );
    }
}

void MenuLevels::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 25, 50, 90, 255 );
    SDL_RenderClear( game->getRenderer() );

    SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_backgroundBox );

    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }

    m_tooltipManager.render( game );
}

void MenuLevels::handleClick( Engine* game, MenuState* state, int id ) {
    switch( id ) {
    case BUTTON_ID_BACK:     state->changeMenuState( MENU_MAIN ); break;
    // case BUTTON_ID_UPGRADES: state->changeMenuState( MENU_UPGRADES ); break;
    case BUTTON_ID_LEVEL_1:  m_stateEnd = true; m_levelPath = "media/data/level_1.tmx"; break;
    }
}
