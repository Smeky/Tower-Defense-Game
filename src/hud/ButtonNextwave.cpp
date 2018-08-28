#include "hud\ButtonNextwave.h"

ButtonNextwave::ButtonNextwave( int x, int y, int w, int h, int id ) : IButton( x, y, w, h, id ) {
    m_hotkey = SDLK_SPACE;

    m_alphaVelocity = 2000;
}

void ButtonNextwave::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        m_alpha = 0.0;
    }
    else {
        if( m_mouseover ) {
            if( m_alpha < 255 ) {
                m_alpha += m_alphaVelocity * timeStep;

                if( m_alpha > 255 ) m_alpha = 255;
            }
        }
        else {
            if( m_alpha > 0.0 ) {
                m_alpha -= m_alphaVelocity * timeStep;

                if( m_alpha < 0.0 ) m_alpha = 0.0;
            }
        }
    }
}

void ButtonNextwave::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 80, 90, 110, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    SDL_SetRenderDrawColor( game->getRenderer(), 220, 200, 0, m_alpha );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    game->drawTexture( "TEXT_BUTTON_NEXTWAVE", m_box.x + m_box.w / 2, m_box.y + m_box.h / 2 + 1, NULL, NULL, true, true );
}
