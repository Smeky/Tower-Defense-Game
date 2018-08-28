#include "IButton.h"

#include "iostream"
using namespace std;

IButton::IButton( int x, int y, int w, int h, int id ) {
    m_box.x = x;
    m_box.y = y;
    m_box.w = w;
    m_box.h = h;

    m_id            = id;
    m_hotkey        = 0;
    m_alpha         = 0.0;
    m_alphaVelocity = 0;

    m_clicked   = false;
    m_pressed   = false;
    m_mouseover = false;
    m_selected  = false;
}

IButton::IButton( int id ) {
    m_box   = { 0, 0, 0, 0 };
    m_id    = id;

    m_hotkey        = 0;
    m_alpha         = 0.0;
    m_alphaVelocity = 0;

    m_clicked   = false;
    m_pressed   = false;
    m_mouseover = false;
    m_selected  = false;
}

void IButton::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    if( game->checkMouseover( mousePosition, &m_box ) ) {
        m_mouseover = true;
    }
    else {
        m_mouseover = false;
    }

    if( m_mouseover ) {
        if( event.type == SDL_MOUSEBUTTONDOWN ) {
            if( event.button.button == SDL_BUTTON_LEFT ) {
                m_pressed = true;
            }
        }
    }

    if( event.type == SDL_MOUSEBUTTONUP ) {
        if( event.button.button == SDL_BUTTON_LEFT ) {
            if( m_mouseover ) {
                if( m_pressed ) {
                    m_clicked = true;
                }
            }
            else m_clicked = false;

            m_pressed = false;
        }
    }

    if( event.type == SDL_KEYDOWN && !event.key.repeat ) {
        if( event.key.keysym.sym == m_hotkey ) {
            m_clicked = true;
        }
    }
}

void IButton::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        m_clicked   = false;
        m_mouseover = false;
    }
}

void IButton::setXPosition( int x ) {
    m_box.x = x;
}

void IButton::setYPosition( int y ) {
    m_box.y = y;
}
