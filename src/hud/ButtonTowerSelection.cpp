#include "hud\ButtonTowerSelection.h"

ButtonTowerSelection::ButtonTowerSelection( Tower_data data, SDL_Rect box, SDL_Keycode hotkey, int id ) : IButton( box.x, box.y, box.w, box.h, id ) {
    m_towerData = data;
    m_hotkey    = hotkey;

    m_towerBox.w = box.h * 0.75;
    m_towerBox.h = box.h * 0.75;
    m_towerBox.x = box.x + box.w / 2;
    m_towerBox.y = box.y + box.h / 2;

    m_alphaVelocity = 1000;
}

void ButtonTowerSelection::update( Engine* game, float timeStep ) {
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

void ButtonTowerSelection::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 15, 25, 35, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    SDL_SetRenderDrawColor( game->getRenderer(), 15, 70, 100, (int)m_alpha );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    if( m_clicked ) {
        SDL_SetRenderDrawColor( game->getRenderer(), 25, 100, 150, 255 );
        SDL_RenderFillRect( game->getRenderer(), &m_box );
    }

    game->drawTexture( m_towerData.tex_body,   m_towerBox.x, m_towerBox.y, NULL, &m_towerBox,  true, true );
    game->drawTexture( m_towerData.tex_cannon, m_towerBox.x, m_towerBox.y, NULL, NULL,  true, true );
}
