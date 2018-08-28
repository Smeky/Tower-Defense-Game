#include "OptionsPgAudio.h"
#include "ButtonMenu.h"
#include "ButtonCheckbox.h"

typedef std::vector<IButton*> _Button;
typedef std::vector<Slider*> _Slider;

using namespace std;

enum buttons_id {
    BUTTON_APPLY,
};

enum checkboxes_id {
    CHECKBOX_SOUND,
    CHECKBOX_MUSIC,
};

void OptionsPgAudio::init( Engine* game, SDL_Rect box ) {
    m_bgBox = box;

    m_buttons.push_back( new ButtonMenu( "TEXT_BUTTON_APPLY",
                                         m_bgBox.x + m_bgBox.w - 140, m_bgBox.y + m_bgBox.h - 35, 130, 25,
                                         BUTTON_APPLY ) );

    m_checkboxes.push_back( new ButtonCheckbox( { m_bgBox.x + 35, m_bgBox.y + 35, 20, 20 }, CHECKBOX_SOUND ) );
    m_checkboxes.push_back( new ButtonCheckbox( { m_bgBox.x + 35, m_bgBox.y + 120, 20, 20 }, CHECKBOX_MUSIC ) );

    m_sliders.push_back( new Slider( m_bgBox.x + 35, m_bgBox.y + 70, 140, 0, 128, 64 ) );
    m_sliders.push_back( new Slider( m_bgBox.x + 35, m_bgBox.y + 155, 140, 0, 128, 64 ) );
}

void OptionsPgAudio::close() {
    MenuPage::close();

    while( !m_checkboxes.empty() )  delete m_checkboxes.back(), m_checkboxes.pop_back();
    while( !m_sliders.empty() )     delete m_sliders.back(),    m_sliders.pop_back();

    m_checkboxChange.clear();
}

void OptionsPgAudio::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    MenuPage::handleEvents( game, event, mousePos );

    for ( _Button::iterator it = m_checkboxes.begin(); it != m_checkboxes.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }

    for ( _Slider::iterator it = m_sliders.begin(); it != m_sliders.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }
}

void OptionsPgAudio::update( Engine* game, float timeStep ) {
    for( _Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            handleClick( game, (*it)->getID() );
        }
    }

    MenuPage::update( game, timeStep );

    for ( _Button::iterator it = m_checkboxes.begin(); it != m_checkboxes.end(); it++ ) {
        if( (*it)->isClicked() ) {
            m_checkboxChange.push_back( (*it)->getID() );
        }

        (*it)->update( game, timeStep );
    }

    for ( _Slider::iterator it = m_sliders.begin(); it != m_sliders.end(); it++ ) {
        (*it)->update( game,timeStep );
    }
}

void OptionsPgAudio::render( Engine* game ) {
    MenuPage::render( game );

    for ( _Button::iterator it = m_checkboxes.begin(); it != m_checkboxes.end(); it++ ) {
        (*it)->render( game );
    }

    for ( _Slider::iterator it = m_sliders.begin(); it != m_sliders.end(); it++ ) {
        (*it)->render( game );
    }

    game->drawTexture( "TEXT_OPTIONS_ENABLE_SOUND", m_bgBox.x + 65, m_bgBox.y + 45  + 1, NULL, NULL, false, true );
    game->drawTexture( "TEXT_OPTIONS_ENABLE_MUSIC", m_bgBox.x + 65, m_bgBox.y + 130 + 1, NULL, NULL, false, true );
}

void OptionsPgAudio::handleClick( Engine* game, int id ) {
    switch( id ) {
    case BUTTON_APPLY:
        manageCheckboxes( game );
        break;
    }
}

void OptionsPgAudio::manageCheckboxes( Engine* game ) {
    for( _Button::iterator it = m_checkboxes.begin(); it != m_checkboxes.end(); it++ ) {
        for( unsigned int i = 0; i != m_checkboxChange.size(); i++ ) {
            if( m_checkboxChange[ i ] == (*it)->getID() ) {
                if( (*it)->isSelected() ) {
                    switch( (*it)->getID() ) {
                    case CHECKBOX_SOUND: game->Sounds()->muteSound( true ); break;
                    case CHECKBOX_MUSIC: game->Sounds()->muteMusic( true ); break;
                    }
                }
                else {
                    switch( (*it)->getID() ) {
                    case CHECKBOX_SOUND: game->Sounds()->muteSound( false ); break;
                    case CHECKBOX_MUSIC: game->Sounds()->muteMusic( false ); break;
                    }
                }
            }
        }
    }
}
