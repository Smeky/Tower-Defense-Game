#include "hud\ButtonLevel.h"

ButtonLevel::ButtonLevel( SDL_Rect box, int id, bool unlocked, bool defeated ) : IButton( box.x, box.y, box.w, box.h, id ) {
    m_unlocked = unlocked;
    m_defeated = defeated;
}

void ButtonLevel::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        m_clicked   = false;
        m_mouseover = false;
    }
}

void ButtonLevel::render( Engine* game ) {
    SDL_Rect clip = { 0, 0, 30, 30 };

    if( m_unlocked ) {
        if( !m_defeated ) {
            if( !m_mouseover ) {
                clip.y = clip.h;
            }
            else {
                clip.y = clip.h * 2;
            }
        }
        else {
            if( !m_mouseover ) {
                clip.x = clip.w;
                clip.y = clip.h;
            }
            else {
                clip.x = clip.w;
                clip.y = clip.h * 2;
            }
        }
    }

    game->drawTexture( "BUTTON_LEVEL", m_box.x, m_box.y, &clip );
}
