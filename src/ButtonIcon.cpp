#include "ButtonIcon.h"

#include "iostream"
using namespace std;

ButtonIcon::ButtonIcon( std::string icon, SDL_Rect box, SDL_Keycode hotkey, int id ) : IButton( box.x - box.w / 2, box.y - box.h / 2, box.w, box.h, id ) {
    m_hotkey    = hotkey;
    m_icon      = icon;
}

void ButtonIcon::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        m_clicked   = false;
    }
}

void ButtonIcon::render( Engine* game ) {
    if( m_icon != "NO_TEXTURE" ) {
        SDL_Rect clip = { 0, 0, game->getTextureW( m_icon ) / 2, game->getTextureH( m_icon ) };

        if( m_mouseover ) {
            clip.x = clip.w;
        }

        game->drawTexture( m_icon, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2, &clip, &m_box, true, true );
    }
    else {
        if( m_mouseover || m_pressed ) {
            SDL_SetRenderDrawColor( game->getRenderer(), 0, 255, 0, 255 );
        }
        else {
            SDL_SetRenderDrawColor( game->getRenderer(), 255, 0, 0, 255 );
        }

        SDL_RenderDrawRect( game->getRenderer(), &m_box );
    }

}

void ButtonIcon::setPosition( int x, int y ) {
    m_box.x = x;
    m_box.y = y;
}
