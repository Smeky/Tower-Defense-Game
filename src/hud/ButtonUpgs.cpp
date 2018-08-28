#include "ButtonUpgs.h"

#include "iostream"
using namespace std;

ButtonUpgs::ButtonUpgs( std::string text_adrs, int x, int y, int w, int h, int id ) : IButton( x, y, w, h, id ) {
    m_textAdrs = text_adrs;
}

void ButtonUpgs::update( Engine* game ) {

}

void ButtonUpgs::render( Engine* game ) {
    SDL_Rect clip = { 0, 0, game->getTextureW( m_textAdrs ), game->getTextureH( m_textAdrs ) / 3 };

    if( m_mouseover ) {
        clip.y = clip.h;

    }
    if( m_clicked ) {
        clip.y = clip.h * 2;
    }

    game->drawTexture( m_textAdrs, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2, &clip, NULL, true, true );
}
