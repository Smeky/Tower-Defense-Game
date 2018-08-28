#include "hud\TooltipWarning.h"
#include "core\SDL2_gfxPrimitives.h"

TooltipWarning::TooltipWarning( std::string text, SDL_Rect box, int arrow_side ) {
    m_text  = text;
    m_box   = box;

    if( arrow_side == TOOLTIP_LEFT ) {
        m_box.x = m_box.x - m_box.w;
        m_box.y = m_box.y - m_box.h / 2;
    }
    else if( arrow_side == TOOLTIP_RIGHT ) {
        m_box.y = m_box.y - m_box.h / 2;
    }
    else if( arrow_side == TOOLTIP_UP ) {
        m_box.x = m_box.x - m_box.w / 2;
        m_box.y = m_box.y - m_box.h;
    }
    else if( arrow_side == TOOLTIP_DOWN ) {
        m_box.x = m_box.x - m_box.w / 2;
    }

    if( arrow_side == TOOLTIP_NONE ) {
        m_arrowPoint[ 0 ].x = -1;
        m_arrowPoint[ 0 ].y = -1;
        m_arrowPoint[ 1 ].x = -1;
        m_arrowPoint[ 1 ].y = -1;
        m_arrowPoint[ 2 ].x = -1;
        m_arrowPoint[ 2 ].y = -1;

        m_borderPoint[ 0 ].x = m_box.x;
        m_borderPoint[ 0 ].y = m_box.y;
        m_borderPoint[ 1 ].x = m_box.x + m_box.w;
        m_borderPoint[ 1 ].y = m_box.y;
        m_borderPoint[ 2 ].x = m_box.x + m_box.w;
        m_borderPoint[ 2 ].y = m_box.y + m_box.h;
        m_borderPoint[ 3 ].x = m_box.x;
        m_borderPoint[ 3 ].y = m_box.y + m_box.h;
        m_borderPoint[ 4 ].x = m_box.x;
        m_borderPoint[ 4 ].y = m_box.y;
        m_borderPoint[ 5 ].x = m_box.x;
        m_borderPoint[ 5 ].y = m_box.y;
        m_borderPoint[ 6 ].x = m_box.x;
        m_borderPoint[ 6 ].y = m_box.y;
        m_borderPoint[ 7 ].x = m_box.x;
        m_borderPoint[ 7 ].y = m_box.y;

        m_borderBGPoint[ 0 ].x = m_box.x - 1;
        m_borderBGPoint[ 0 ].y = m_box.y - 1;
        m_borderBGPoint[ 1 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 1 ].y = m_box.y - 1;
        m_borderBGPoint[ 2 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 2 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 3 ].x = m_box.x - 1;
        m_borderBGPoint[ 3 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 4 ].x = m_box.x - 1;
        m_borderBGPoint[ 4 ].y = m_box.y - 1;
        m_borderBGPoint[ 5 ].x = m_box.x - 1;
        m_borderBGPoint[ 5 ].y = m_box.y - 1;
        m_borderBGPoint[ 6 ].x = m_box.x - 1;
        m_borderBGPoint[ 6 ].y = m_box.y - 1;
        m_borderBGPoint[ 7 ].x = m_box.x - 1;
        m_borderBGPoint[ 7 ].y = m_box.y - 1;
    }
    else if( arrow_side == TOOLTIP_LEFT ) {
        m_arrowPoint[ 0 ].x = m_box.x + m_box.w;
        m_arrowPoint[ 0 ].y = m_box.y + m_box.h * 0.25;
        m_arrowPoint[ 1 ].x = m_box.x + m_box.w;
        m_arrowPoint[ 1 ].y = m_box.y + m_box.h * 0.75;
        m_arrowPoint[ 2 ].x = m_box.x + m_box.w + m_box.h * 0.25;
        m_arrowPoint[ 2 ].y = m_box.y + m_box.h / 2;

        m_borderPoint[ 0 ].x = m_box.x;
        m_borderPoint[ 0 ].y = m_box.y;
        m_borderPoint[ 1 ].x = m_box.x + m_box.w - 1;
        m_borderPoint[ 1 ].y = m_box.y;
        m_borderPoint[ 2 ].x = m_box.x + m_box.w - 1;
        m_borderPoint[ 2 ].y = m_box.y + m_box.h * 0.25;
        m_borderPoint[ 3 ].x = m_box.x + m_box.w + m_box.h * 0.25 - 1;
        m_borderPoint[ 3 ].y = m_box.y + m_box.h * 0.5;
        m_borderPoint[ 4 ].x = m_box.x + m_box.w - 1;
        m_borderPoint[ 4 ].y = m_box.y + m_box.h * 0.75;
        m_borderPoint[ 5 ].x = m_box.x + m_box.w - 1;
        m_borderPoint[ 5 ].y = m_box.y + m_box.h - 1;
        m_borderPoint[ 6 ].x = m_box.x;
        m_borderPoint[ 6 ].y = m_box.y + m_box.h - 1;
        m_borderPoint[ 7 ].x = m_box.x;
        m_borderPoint[ 7 ].y = m_box.y;

        m_borderBGPoint[ 0 ].x = m_box.x - 1;
        m_borderBGPoint[ 0 ].y = m_box.y - 1;
        m_borderBGPoint[ 1 ].x = m_box.x + m_box.w;
        m_borderBGPoint[ 1 ].y = m_box.y - 1;
        m_borderBGPoint[ 2 ].x = m_box.x + m_box.w;
        m_borderBGPoint[ 2 ].y = m_box.y + m_box.h * 0.25 - 1;
        m_borderBGPoint[ 3 ].x = m_box.x + m_box.w + m_box.h * 0.25 + 1;
        m_borderBGPoint[ 3 ].y = m_box.y + m_box.h * 0.5;
        m_borderBGPoint[ 4 ].x = m_box.x + m_box.w;
        m_borderBGPoint[ 4 ].y = m_box.y + m_box.h * 0.75 + 1;
        m_borderBGPoint[ 5 ].x = m_box.x + m_box.w;
        m_borderBGPoint[ 5 ].y = m_box.y + m_box.h;
        m_borderBGPoint[ 6 ].x = m_box.x - 1;
        m_borderBGPoint[ 6 ].y = m_box.y + m_box.h;
        m_borderBGPoint[ 7 ].x = m_box.x - 1;
        m_borderBGPoint[ 7 ].y = m_box.y - 1;
    }
    else if( arrow_side == TOOLTIP_RIGHT ) {
        m_arrowPoint[ 0 ].x = m_box.x - 1;
        m_arrowPoint[ 0 ].y = m_box.y + m_box.h * 0.25;
        m_arrowPoint[ 1 ].x = m_box.x - 1;
        m_arrowPoint[ 1 ].y = m_box.y + m_box.h * 0.75;
        m_arrowPoint[ 2 ].x = m_box.x - m_box.h * 0.25 - 1;
        m_arrowPoint[ 2 ].y = m_box.y + m_box.h / 2;

        m_borderPoint[ 0 ].x = m_box.x;
        m_borderPoint[ 0 ].y = m_box.y;
        m_borderPoint[ 1 ].x = m_box.x + m_box.w;
        m_borderPoint[ 1 ].y = m_box.y;
        m_borderPoint[ 2 ].x = m_box.x + m_box.w;
        m_borderPoint[ 2 ].y = m_box.y + m_box.h;
        m_borderPoint[ 3 ].x = m_box.x;
        m_borderPoint[ 3 ].y = m_box.y + m_box.h;
        m_borderPoint[ 4 ].x = m_box.x;
        m_borderPoint[ 4 ].y = m_box.y + m_box.h * 0.75;
        m_borderPoint[ 5 ].x = m_box.x - m_box.h * 0.25;
        m_borderPoint[ 5 ].y = m_box.y + m_box.h / 2;
        m_borderPoint[ 6 ].x = m_box.x;
        m_borderPoint[ 6 ].y = m_box.y + m_box.h * 0.25;
        m_borderPoint[ 7 ].x = m_box.x;
        m_borderPoint[ 7 ].y = m_box.y;

        m_borderBGPoint[ 0 ].x = m_box.x - 1;
        m_borderBGPoint[ 0 ].y = m_box.y - 1;
        m_borderBGPoint[ 1 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 1 ].y = m_box.y - 1;
        m_borderBGPoint[ 2 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 2 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 3 ].x = m_box.x - 1;
        m_borderBGPoint[ 3 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 4 ].x = m_box.x - 1;
        m_borderBGPoint[ 4 ].y = m_box.y + m_box.h * 0.75;
        m_borderBGPoint[ 5 ].x = m_box.x - m_box.h * 0.25 - 1;
        m_borderBGPoint[ 5 ].y = m_box.y + m_box.h / 2;
        m_borderBGPoint[ 6 ].x = m_box.x - 1;
        m_borderBGPoint[ 6 ].y = m_box.y + m_box.h * 0.25;
        m_borderBGPoint[ 7 ].x = m_box.x - 1;
        m_borderBGPoint[ 7 ].y = m_box.y - 1;
    }
    else if( arrow_side == TOOLTIP_UP ) {
        m_arrowPoint[ 0 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_arrowPoint[ 0 ].y = m_box.y + m_box.h;
        m_arrowPoint[ 1 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_arrowPoint[ 1 ].y = m_box.y + m_box.h;
        m_arrowPoint[ 2 ].x = m_box.x + m_box.w * 0.5;
        m_arrowPoint[ 2 ].y = m_box.y + m_box.h + m_box.h * 0.25;

        m_borderPoint[ 0 ].x = m_box.x;
        m_borderPoint[ 0 ].y = m_box.y;
        m_borderPoint[ 1 ].x = m_box.x + m_box.w;
        m_borderPoint[ 1 ].y = m_box.y;
        m_borderPoint[ 2 ].x = m_box.x + m_box.w;
        m_borderPoint[ 2 ].y = m_box.y + m_box.h;
        m_borderPoint[ 3 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_borderPoint[ 3 ].y = m_box.y + m_box.h;
        m_borderPoint[ 4 ].x = m_box.x + m_box.w * 0.5;
        m_borderPoint[ 4 ].y = m_box.y + m_box.h + m_box.h * 0.25;
        m_borderPoint[ 5 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_borderPoint[ 5 ].y = m_box.y + m_box.h;
        m_borderPoint[ 6 ].x = m_box.x;
        m_borderPoint[ 6 ].y = m_box.y + m_box.h;
        m_borderPoint[ 7 ].x = m_box.x;
        m_borderPoint[ 7 ].y = m_box.y;

        m_borderBGPoint[ 0 ].x = m_box.x - 1;
        m_borderBGPoint[ 0 ].y = m_box.y - 1;
        m_borderBGPoint[ 1 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 1 ].y = m_box.y - 1;
        m_borderBGPoint[ 2 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 2 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 3 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_borderBGPoint[ 3 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 4 ].x = m_box.x + m_box.w * 0.5;
        m_borderBGPoint[ 4 ].y = m_box.y + m_box.h + m_box.h * 0.25 + 1;
        m_borderBGPoint[ 5 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_borderBGPoint[ 5 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 6 ].x = m_box.x - 1;
        m_borderBGPoint[ 6 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 7 ].x = m_box.x - 1;
        m_borderBGPoint[ 7 ].y = m_box.y - 1;
    }
    else if( arrow_side == TOOLTIP_DOWN ) {
        m_arrowPoint[ 0 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_arrowPoint[ 0 ].y = m_box.y;
        m_arrowPoint[ 1 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_arrowPoint[ 1 ].y = m_box.y;
        m_arrowPoint[ 2 ].x = m_box.x + m_box.w * 0.5;
        m_arrowPoint[ 2 ].y = m_box.y - m_box.h * 0.25;

        m_borderPoint[ 0 ].x = m_box.x;
        m_borderPoint[ 0 ].y = m_box.y;
        m_borderPoint[ 1 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_borderPoint[ 1 ].y = m_box.y;
        m_borderPoint[ 2 ].x = m_box.x + m_box.w * 0.5;
        m_borderPoint[ 2 ].y = m_box.y - m_box.h * 0.25;
        m_borderPoint[ 3 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_borderPoint[ 3 ].y = m_box.y;
        m_borderPoint[ 4 ].x = m_box.x + m_box.w;
        m_borderPoint[ 4 ].y = m_box.y;
        m_borderPoint[ 5 ].x = m_box.x + m_box.w;
        m_borderPoint[ 5 ].y = m_box.y + m_box.h;
        m_borderPoint[ 6 ].x = m_box.x;
        m_borderPoint[ 6 ].y = m_box.y + m_box.h;
        m_borderPoint[ 7 ].x = m_box.x;
        m_borderPoint[ 7 ].y = m_box.y;

        m_borderBGPoint[ 0 ].x = m_box.x - 1;
        m_borderBGPoint[ 0 ].y = m_box.y - 1;
        m_borderBGPoint[ 1 ].x = m_box.x + m_box.w * 0.5 - m_box.h * 0.25;
        m_borderBGPoint[ 1 ].y = m_box.y - 1;
        m_borderBGPoint[ 2 ].x = m_box.x + m_box.w * 0.5;
        m_borderBGPoint[ 2 ].y = m_box.y - m_box.h * 0.25 - 1;
        m_borderBGPoint[ 3 ].x = m_box.x + m_box.w * 0.5 + m_box.h * 0.25;
        m_borderBGPoint[ 3 ].y = m_box.y - 1;
        m_borderBGPoint[ 4 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 4 ].y = m_box.y - 1;
        m_borderBGPoint[ 5 ].x = m_box.x + m_box.w + 1;
        m_borderBGPoint[ 5 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 6 ].x = m_box.x - 1;
        m_borderBGPoint[ 6 ].y = m_box.y + m_box.h + 1;
        m_borderBGPoint[ 7 ].x = m_box.x - 1;
        m_borderBGPoint[ 7 ].y = m_box.y - 1;
    }

    m_doFade        = false;
    m_faded         = false;
    m_alpha         = 254;
    m_fadeVelocity  = 1500;
}

void TooltipWarning::update( Engine* game ) {
    if( m_doFade ) {
        m_alpha -= m_fadeVelocity * game->getTimeDelta();

        if( m_alpha <= 0 ) {
            m_alpha = 0;

            m_faded = true;
        }
    }
}

void TooltipWarning::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 170, 15, 20, m_alpha );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    filledTrigonRGBA( game->getRenderer(), m_arrowPoint[ 0 ].x, m_arrowPoint[ 0 ].y,
                                           m_arrowPoint[ 1 ].x, m_arrowPoint[ 1 ].y,
                                           m_arrowPoint[ 2 ].x, m_arrowPoint[ 2 ].y, 170, 15, 20, m_alpha );

    SDL_SetRenderDrawColor( game->getRenderer(), 0, 0, 0, m_alpha );
    SDL_RenderDrawLines( game->getRenderer(), m_borderBGPoint, 8 );

    SDL_SetRenderDrawColor( game->getRenderer(), 200, 80, 80, m_alpha );
    SDL_RenderDrawLines( game->getRenderer(), m_borderPoint, 8 );

    game->setTextureAlpha( m_text, m_alpha );
    game->drawTexture( m_text, m_box.x + m_box.w / 2, m_box.y + m_box.h / 2 + 1, NULL, NULL, true, true );
}
