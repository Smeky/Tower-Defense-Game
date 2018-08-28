#include "ButtonMenuPage.h"

#include "iostream"
using namespace std;

ButtonMenuPage::ButtonMenuPage( std::string text, SDL_Rect box, int id, SDL_Keycode hotkey ) : IButton( box.x, box.y, box.w, box.h, id ) {
    m_text      = text;
    m_hotkey    = hotkey;
}

void ButtonMenuPage::render( Engine* game ) {
    SDL_Rect clip = { 0, 0, game->getTextureW( m_text ), game->getTextureH( m_text ) / 4 };

    SDL_SetRenderDrawColor( game->getRenderer(), 40, 40, 40, 200 );

    if( m_mouseover ) {
        clip.y = clip.h;

        SDL_SetRenderDrawColor( game->getRenderer(), 40, 40, 40, 200 );
    }
    if( m_pressed ) {
        clip.y = clip.h * 2;

        SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    }
    if( m_selected ) {
        clip.y = clip.h * 3;

        SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    }

    SDL_RenderFillRect( game->getRenderer(), &m_box );

    game->drawTexture( m_text, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2, &clip, NULL, true, true );
}
