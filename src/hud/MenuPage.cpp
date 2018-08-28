#include "MenuPage.h"

using namespace std;

typedef std::vector<IButton*> _Button;

void MenuPage::close() {
    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();
}

void MenuPage::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    for( _Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }
}

void MenuPage::update( Engine* game, float timeStep ) {
    for( _Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->update( game, timeStep );
    }
}

void MenuPage::render( Engine* game ) {
    for( _Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }
}
