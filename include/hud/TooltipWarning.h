#ifndef TOOLTIPMESSAGE_H
#define TOOLTIPMESSAGE_H

#include "TooltipManager.h"

class TooltipWarning {
public:
    TooltipWarning( std::string text, SDL_Rect box, int arrow_side );

    void doFade() { m_doFade = true; }
    bool isFaded() { return m_faded; }

    void update( Engine* game );
    void render( Engine* game );
private:
    SDL_Rect m_box;
    SDL_Rect m_bgBox;
    std::string m_text;
    SDL_Point m_arrowPoint[ 3 ];
    SDL_Point m_borderPoint[ 8 ];
    SDL_Point m_borderBGPoint[ 8 ];
    bool    m_doFade;
    bool    m_faded;
    float   m_alpha;
    int     m_fadeVelocity;
};

#endif // TOOLTIPMESSAGE_H
