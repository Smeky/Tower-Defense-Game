#include "hud\ButtonMenu.h"

ButtonMenu::ButtonMenu( std::string text_name, int x, int y, int w, int h, int id, SDL_Keycode hotkey ) : IButton( x, y, w, h, id ) {
    m_text      = text_name;
    m_hotkey    = hotkey;
}

void ButtonMenu::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        game->playSound( "UI_BUTTON_PRESS" );

        m_clicked   = false;
        m_mouseover = false;
    }
}

void ButtonMenu::render( Engine* game ) {
    if( m_mouseover ) {
        // Button color
        SDL_SetRenderDrawColor( game->getRenderer(), 20, 50, 80, 255 );
        SDL_RenderFillRect( game->getRenderer(), &m_box );
    }
    else {
        // Button background color
        SDL_SetRenderDrawColor( game->getRenderer(), 5, 40, 65, 255 );
        SDL_RenderFillRect( game->getRenderer(), &m_box );

        // Button border color
        SDL_SetRenderDrawColor( game->getRenderer(), 160, 160, 160, 80 );
        SDL_RenderDrawRect( game->getRenderer(), &m_box );
    }

    game->drawTexture( m_text, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2 + 1, NULL, NULL, true, true );
}
