#include "hud\ButtonTowerSlower.h"

ButtonTowerSlower::ButtonTowerSlower( int x, int y, int w, int h, int id ) : IButton( x, y, w, h, id ) {
    m_hotkey = SDLK_3;

    m_towerBox.w = h * 0.75;
    m_towerBox.h = h * 0.75;
    m_towerBox.x = x + w / 2;
    m_towerBox.y = y + h / 2;

    m_alphaVelocity = 1000;
}

void ButtonTowerSlower::update( Engine* game, float timeStep ) {
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

                if( m_alpha < 0.0 ) m_alpha = 00.0;
            }
        }
    }
}

void ButtonTowerSlower::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 15, 25, 35, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    SDL_SetRenderDrawColor( game->getRenderer(), 15, 70, 100, (int)m_alpha );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    if( m_clicked ) {
        SDL_SetRenderDrawColor( game->getRenderer(), 25, 100, 150, 255 );
        SDL_RenderFillRect( game->getRenderer(), &m_box );
    }

    game->drawTexture( "TOWER_SLOWER",  m_towerBox.x, m_towerBox.y, NULL, &m_towerBox, true, true );
    game->drawTexture( "CANNON_SLOWER", m_box.x + m_box.w / 2, m_box.y + m_box.h / 2.6,  NULL, NULL, true, true );
}
