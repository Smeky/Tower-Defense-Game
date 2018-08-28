#include "hud\MenuMain.h"

#include "MenuState.h"
#include "hud\ButtonMenu.h"

#include "PlayState.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> _button;

enum BUTTON_ID {
    BUTTON_ID_LEVELS,
    BUTTON_ID_OPTIONS,
    BUTTON_ID_ACHIEVMENTS,
    BUTTON_ID_EXIT,
};

void MenuMain::init( Engine* game ) {
    m_centerBox.w = 244;
    m_centerBox.h = 320;
    m_centerBox.x = ( game->getWindowW() - m_centerBox.w ) / 2;
    m_centerBox.y = ( game->getWindowH() - m_centerBox.h ) / 2;

    m_temporaryBox.x = m_centerBox.x;
    m_temporaryBox.y = m_centerBox.y + m_centerBox.h + 5;
    m_temporaryBox.w = m_centerBox.w;
    m_temporaryBox.h = 30;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_LEVELS",      m_centerBox.x + m_centerBox.w / 6, m_centerBox.y + m_centerBox.h / 8 + ( m_centerBox.w / 9 + 5 ) * 0, m_centerBox.w / 1.5, m_centerBox.w / 9, BUTTON_ID_LEVELS ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_OPTIONS",     m_centerBox.x + m_centerBox.w / 6, m_centerBox.y + m_centerBox.h / 8 + ( m_centerBox.w / 9 + 5 ) * 1, m_centerBox.w / 1.5, m_centerBox.w / 9, BUTTON_ID_OPTIONS ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_ACHIEVMENTS", m_centerBox.x + m_centerBox.w / 6, m_centerBox.y + m_centerBox.h / 8 + ( m_centerBox.w / 9 + 5 ) * 2, m_centerBox.w / 1.5, m_centerBox.w / 9, BUTTON_ID_ACHIEVMENTS ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_EXIT",        m_centerBox.x + m_centerBox.w / 6, m_centerBox.y + m_centerBox.h / 8 + ( m_centerBox.w / 9 + 5 ) * 7, m_centerBox.w / 1.5, m_centerBox.w / 9, BUTTON_ID_EXIT ) );
}

void MenuMain::close() {
    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();

    m_tooltipManager.close();
}

void MenuMain::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePosition );
    }
}

void MenuMain::update( Engine* game, MenuState* state, float timeStep ) {
    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, state, (*it)->getID() );
        }

        (*it)->update( game, timeStep );
    }

    m_tooltipManager.update( game );
}

void MenuMain::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_centerBox );
    SDL_RenderFillRect( game->getRenderer(), &m_temporaryBox );

    game->drawTexture( "MENU_TITLE", m_centerBox.x + m_centerBox.w / 2, m_centerBox.y / 2, NULL, NULL, true, true );
    game->drawTexture( "TEXT_TEMPORARY", m_temporaryBox.x + m_temporaryBox.w / 2, m_temporaryBox.y + m_temporaryBox.h / 2, NULL, NULL, true, true );

    for( _button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }

    m_tooltipManager.render( game );
}

void MenuMain::handleClick( Engine* game, MenuState* state, int id ) {
    switch( id ) {
    case BUTTON_ID_LEVELS:      state->changeMenuState( MENU_PLAY );  m_tooltipManager.close(); break;
    case BUTTON_ID_OPTIONS:     state->changeMenuState( MENU_OPTIONS ); m_tooltipManager.close(); break;
    case BUTTON_ID_ACHIEVMENTS:
        m_tooltipManager.createTooltipWarningRight( game, "TEXT_TOOLTIP_NOT_DONE",
                                               m_buttons[ BUTTON_ID_ACHIEVMENTS ]->getBox().x + m_buttons[ BUTTON_ID_ACHIEVMENTS ]->getBox().w + 20,
                                               m_buttons[ BUTTON_ID_ACHIEVMENTS ]->getBox().y + m_buttons[ BUTTON_ID_ACHIEVMENTS ]->getBox().h / 2,
                                               true );
        game->playSound( "SOUND_UI_ERROR" );
        break;
    case BUTTON_ID_EXIT:        game->setQuit(); break;
    }
}
