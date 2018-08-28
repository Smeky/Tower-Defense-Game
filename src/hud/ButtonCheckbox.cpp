#include "ButtonCheckbox.h"

ButtonCheckbox::ButtonCheckbox( SDL_Rect box, int id ) : IButton( box.x, box.y, box.w, box.h, id ) {}

void ButtonCheckbox::update( Engine* game, float timeStep ) {
    if( m_clicked ) {
        if( !m_selected ) {
            m_selected = true;
        }
        else {
            m_selected = false;
        }

        game->playSound( "UI_BUTTON_PRESS" );

        m_clicked   = false;
    }
}

void ButtonCheckbox::render( Engine* game ) {
    SDL_Rect clip = { 0, 0, game->getTextureW( "BUTTON_CHECKBOX" ), game->getTextureH( "BUTTON_CHECKBOX" ) / 3 };

    if( m_mouseover || m_pressed ) {
        clip.y = clip.h;
    }
    if( m_selected ) {
        clip.y = clip.h * 2;
    }

    game->drawTexture( "BUTTON_CHECKBOX", m_box.x, m_box.y, &clip );
}
