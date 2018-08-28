#include "OptionsPgVideo.h"
#include "ButtonMenu.h"

typedef std::vector<IButton*> _Button;
using namespace std;

enum button_ids {
    BUTTON_RES_1 = 1,
    BUTTON_RES_2,
    BUTTON_RES_3,
};

void OptionsPgVideo::init( Engine* game, SDL_Rect box ) {
    m_bgBox = box;
    m_textResBox.x = m_bgBox.x + 10;
    m_textResBox.y = m_bgBox.y + 10;
    m_textResBox.w = 160;
    m_textResBox.h = 25;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RES_1", m_bgBox.x + 10, m_bgBox.y + 50, 160, 25, BUTTON_RES_1 ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RES_2", m_bgBox.x + 10, m_bgBox.y + 80, 160, 25, BUTTON_RES_2 ) );
    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_RES_3", m_bgBox.x + 10, m_bgBox.y + 110, 160, 25, BUTTON_RES_3 ) );
}

void OptionsPgVideo::update( Engine* game, float timeStep ) {
    for( _Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, (*it)->getID() );
        }
    }

    MenuPage::update( game, timeStep );
}

void OptionsPgVideo::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 0, 0, 0, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_textResBox );

    game->drawTexture( "TEXT_OPTIONS_RESOLUTION", m_textResBox.x + m_textResBox.w / 2, m_textResBox.y + m_textResBox.h / 2 + 1, NULL, NULL, true, true );

    MenuPage::render( game );
}

void OptionsPgVideo::handleClick( Engine* game, int id ) {
    switch( id ) {
    case BUTTON_RES_1: game->setWindowSize( 854, 480 ); break;
    case BUTTON_RES_2: game->setWindowSize( 1024, 576 ); break;
    case BUTTON_RES_3: game->setWindowSize( 1280, 720 ); break;
    }
}
