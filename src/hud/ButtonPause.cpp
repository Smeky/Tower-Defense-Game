#include "hud\ButtonPause.h"

#include "PlayState.h"

ButtonPause::ButtonPause( int x, int y, int w, int h, int id ) : IButton( x, y, w, h, id ) {
    m_hotkey = SDLK_p;
}

void ButtonPause::update( Engine* game ) {
    if( m_clicked ) {

        m_clicked = false;
    }
}

void ButtonPause::render( Engine* game ) {
    SDL_Rect clip;

    clip.x = 0;
    clip.y = 0;
    clip.w = game->getTextureW( "BUTTON_PAUSE" ) / 2;
    clip.h = game->getTextureH( "BUTTON_PAUSE" );

    if( m_mouseover || m_clicked ) {
        clip.x = clip.w;
    }

    game->drawTexture( "BUTTON_PAUSE", m_box.x, m_box.y, &clip, &m_box );
}
