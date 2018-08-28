#include "WaveDisplay.h"

#include "iostream"
using namespace std;

WaveDisplay::WaveDisplay( Engine* game, Enemy_data data, int amount, SDL_Rect waveBox, int id, int y ) : IButton( id ) {
    m_enemyData = data;
    m_amount    = amount;   // Amount of enemies
    m_waveBox   = waveBox;  // Box rectangle

    m_moveVelocity = game->calcByResW( 4 );
    m_skipVelocity = game->calcByResW( 80 );
    m_done         = false;
    m_skip         = false;
    m_textCreated  = false;

    m_box.w = waveBox.w;
    m_box.h = waveBox.h / 10;
    m_box.x = waveBox.x;

    if( y == 0 ) {
        m_box.y = waveBox.y - ( m_box.h - waveBox.h / 20 ) * 2;
    }
    else {
        m_box.y = y;
    }

    m_position = m_box.y;

    m_textureBox.x = m_box.x + m_box.w / 4;
    m_textureBox.w = m_box.w - ( m_box.w / 4 ) * 2;
    m_textureBox.h = m_box.w / 2;
    m_textureBox.y = m_box.y + m_box.w / 4;
}

void WaveDisplay::update( Engine* game, float timeStep ) {
    // If player wants to skip to next way, use skip Velocity
    // Otherwise use normal movement velocity
    if( !m_skip ) {
        m_position += timeStep * m_moveVelocity;
    }
    else {
        m_position += timeStep * m_skipVelocity;
    }

    // If box hits specific position, let enemies spawn
    // Otherwise keep moving
    if( m_position + m_box.h > m_waveBox.y + m_waveBox.h ) {
        m_done = true;
    }
    else {
        m_box.y = (int)m_position;
        m_textureBox.y = m_box.y + m_box.w / 4;
    }
}

void WaveDisplay::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 25, 40, 50, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    if( m_mouseover ) {
        SDL_SetRenderDrawColor( game->getRenderer(), 150, 150, 150, 255 );
    }
    else {
        SDL_SetRenderDrawColor( game->getRenderer(), 50, 75, 95, 255 );
    }

    SDL_RenderDrawRect( game->getRenderer(), &m_box );

    if( !m_textCreated ) {
        m_text.loadFromText( game->intToString( m_amount ), game->getRenderer(), game->getFont( "FONT_CALIBRI_NORMAL" ), { 255, 255, 255 } );
        m_textCreated = true;
    }

    game->drawTexture( m_enemyData.tex, m_textureBox.x, m_textureBox.y, NULL, &m_textureBox );
    m_text.render( m_box.x + m_box.w / 2, m_box.y + m_box.h - m_textureBox.h / 1.5, game->getRenderer(), NULL, NULL, true, true );
}
