#include "MenuState.h"
#include "PlayState.h"
#include "math.h"

#include "iostream"
using namespace std;

MenuState MenuState::m_MenuState;

void MenuState::init( Engine* game ) {
    m_menuState = MENU_MAIN;

    m_menuMain.init( game );
    m_menuPlay.init( game );
    m_menuOptions.init( game );

    m_timer.start();
}

void MenuState::close() {
    m_menuMain.close();
    m_menuPlay.close();
    m_menuOptions.close();
    m_tpManager.close();
}

void MenuState::handleEvents( Engine* game, SDL_Event event ) {
    SDL_Point mousePosition;

    SDL_GetMouseState( &mousePosition.x, &mousePosition.y );

    switch( m_menuState ) {
    case MENU_MAIN:     m_menuMain.handleEvents( game, event, mousePosition ); break;
    case MENU_PLAY: m_menuPlay.handleEvents( game, this, event, mousePosition ); break;
    case MENU_OPTIONS:  m_menuOptions.handleEvents( game, event, mousePosition ); break;
    default: break;
    }

    // Keyborad events
    if( event.type == SDL_KEYDOWN ) {
        switch( event.key.keysym.sym ) {
        case SDLK_ESCAPE: game->setQuit();
        }
    }
}

void MenuState::update( Engine* game ) {
    float timeDelta = m_timer.getTicks() / 1000.f;
    m_timer.start();

    switch( m_menuState ) {
    case MENU_MAIN:     m_menuMain.update( game, this, timeDelta ); break;
    case MENU_PLAY:     m_menuPlay.update( game, this, timeDelta ); break;
    case MENU_OPTIONS:  m_menuOptions.update( game, this, timeDelta ); break;
    default: break;
    }

    m_tpManager.update( game );
}

void MenuState::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 25, 50, 90, 255 );
    SDL_RenderClear( game->getRenderer() );

    switch( m_menuState ) {
    case MENU_MAIN:     m_menuMain.render( game ); break;
    case MENU_PLAY:     m_menuPlay.render( game ); break;
    case MENU_OPTIONS:  m_menuOptions.render( game ); break;
    default: break;
    }

    m_tpManager.render( game );
}

void MenuState::changeMenuState( int state_id ) {
    switch( state_id ) {
    case MENU_MAIN:     m_menuState = MENU_MAIN; break;
    case MENU_PLAY:     m_menuState = MENU_PLAY; break;
    case MENU_OPTIONS:  m_menuState = MENU_OPTIONS; break;
    default: break;
    }
}
