#include "Talent.h"

#include "iostream"
using namespace std;

Talent::Talent( string icon, SDL_Rect box, SDL_Rect bgClip, int id, bool locked, bool used ) : IButton( box.x, box.y, box.w, box.h, id ) {
    m_locked    = locked;
    m_used      = used;
    m_bgClip    = bgClip;
}

void Talent::render( Engine* game ) {
    SDL_Rect clip = m_bgClip;

    if( !m_locked ) {
        if( !m_used ) {
            if( !m_mouseover ) {
                clip.y = clip.h;
            }
            else {
                clip.y = clip.h * 2;
            }
        }
        else {
            if( !m_mouseover ) {
                clip.y = clip.h * 3;
            }
            else {
                clip.y = clip.h* 4;
            }
        }
    }

    game->drawTexture( "GUI_ICON_TALENT_BG", m_box.x, m_box.y, &clip, &m_box );
}
