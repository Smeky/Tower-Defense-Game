#include "MenuPlay.h"
#include "MenuState.h"
#include "PlayState.h"

#include "ButtonIcon.h"
#include "ButtonLevel.h"
#include "ButtonMenuPage.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> _buttons;

enum page_id {
    PAGE_MAP = 1,
    PAGE_TALENTS,
    PAGE_ITEMS
};

enum button_ids {
    ID_MAP = 1,
    ID_TALENTS,
    ID_ITEMS,
    ID_MENU,
};

void MenuPlay::init( Engine* game ) {
    m_bgBox.w = 620;
    m_bgBox.h = 450;
    m_bgBox.x = ( game->getWindowW() - m_bgBox.w ) / 2 + 25;
    m_bgBox.y = ( game->getWindowH() - m_bgBox.h ) / 2;

    m_currPage  = PAGE_MAP;     // Set current menu page to level map

    m_lvManager.init( game, m_bgBox );
    m_tlManager.init( game, m_bgBox );
    m_xpManager.init( game, m_bgBox );

    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_MAP",       { m_bgBox.x - 50, m_bgBox.y + 51 * 0, 50, 50 }, ID_MAP ) );
    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_TALENTS",   { m_bgBox.x - 50, m_bgBox.y + 51 * 1, 50, 50 }, ID_TALENTS ) );
    m_pgButtons.push_back( new ButtonMenuPage( "BUTTON_PAGE_MENU",      { m_bgBox.x - 50, m_bgBox.y + m_bgBox.h - 50, 50, 50 }, ID_MENU ) );
}

void MenuPlay::close() {
    m_tpManager.close();
    m_tlManager.close();
    m_lvManager.close();

    while( !m_pgButtons.empty() ) delete m_pgButtons.back(), m_pgButtons.pop_back();
}

void MenuPlay::handleEvents( Engine* game, MenuState* menu, SDL_Event event, SDL_Point mousePos ) {
    // Let page buttons handle events
    for( _buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }

    // Let buttons based on current page handle events
    switch( m_currPage ) {
    case PAGE_MAP:
        m_lvManager.handleEvents( game, event, mousePos );

        break;
    case PAGE_TALENTS:
        m_tlManager.handleEvents( game, event, mousePos );

        break;
    default: break;
    }
}

void MenuPlay::update( Engine* game, MenuState* menu, float timeStep ) {
    // All buttons checks if they were clicked and update afterwards
    // Let page buttons update
    for( _buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, menu, (*it)->getID() );
        }

        if( m_currPage == (*it)->getID() ) {
            (*it)->setSelect( true );
        }
        else {
            (*it)->setSelect( false );
        }

        (*it)->update( game, timeStep );
    }

    m_xpManager.update( game, timeStep );

    // Let buttons based on current page update
    switch( m_currPage ) {
    case PAGE_MAP:
        m_lvManager.update( game, timeStep );

        break;
    case PAGE_TALENTS:
        m_tlManager.update( game, timeStep );

        break;
    default: break;
    }
}

void MenuPlay::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_bgBox );

    // Let page buttons render
    for( _buttons::iterator it = m_pgButtons.begin(); it != m_pgButtons.end(); it++ ) {
        (*it)->render( game );
    }

    m_xpManager.render( game );

    // Let buttons based on current page rander
    switch( m_currPage ) {
    case PAGE_MAP:
        m_lvManager.render( game );

        break;
    case PAGE_TALENTS:
        m_tlManager.render( game );

        break;
    default: break;
    }
}

void MenuPlay::handleClick( Engine* game, MenuState* menu, int id ) {
    switch( id ) {
    case ID_MENU: menu->changeMenuState( MENU_MAIN ); break;

    case ID_MAP:
        m_currPage = PAGE_MAP;

        break;
    case ID_TALENTS:
        m_currPage = PAGE_TALENTS;

        break;
    case ID_ITEMS:
        m_currPage = PAGE_ITEMS;

        break;
    default: break;
    }

    game->playSound( "UI_BUTTON_PRESS" );
}
