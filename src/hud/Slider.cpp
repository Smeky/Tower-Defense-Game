#include "Slider.h"

#include "iostream"
using namespace std;

Slider::Slider( int x, int y, int w, float minValue, float maxValue, float curValue ) : IButton( 0 ) {
    m_box.h = 14;
    m_box.x = x;
    m_box.y = y + m_box.h / 2;
    m_box.w = w;

    m_minValue = minValue;
    m_maxValue = maxValue;
    m_currentValue = curValue;

    float curValuePos = m_box.x + ( (float)m_box.w / 100 ) * calcPercentCurrentValue();

    m_button = new SliderButton( (int)curValuePos - 5, m_box.y - 3, 10, 20 );
}

Slider::~Slider() {
    delete m_button;
}

void Slider::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    IButton::handleEvents( game, event, mousePos );

    m_button->handleEvents( game, event, mousePos );
}

void Slider::update( Engine* game, float timeStep ) {
    if( m_button->isPressed() ) {
        int x;

        SDL_GetMouseState( &x, NULL );

        if( x < m_box.x ) {
            x = m_box.x;
        }
        else if( x > m_box.x + m_box.w ) {
            x = m_box.x + m_box.w;
        }

        m_currentValue = ( x - m_box.x ) / ( (float)m_box.w / 100 ) * ( m_maxValue / 100 );;

        m_button->setXPosition( x - m_button->getBox().w / 2 );
    }
    else {
        if( m_clicked ) {
            int x;

            SDL_GetMouseState( &x, NULL );

            m_currentValue = ( x - m_box.x ) / ( (float)m_box.w / 100 ) * ( m_maxValue / 100 );;

            m_button->setXPosition( x - m_button->getBox().w / 2 );
        }
    }

    IButton::update( game, timeStep );
    m_button->update( game, timeStep );
}

void Slider::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 0, 255, 0, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_box );

    m_button->render( game );
}

float Slider::getCurrentValueInPercent() {
    return calcPercentCurrentValue();
}

float Slider::calcPercentCurrentValue() {
    return ( m_currentValue - m_minValue ) / ( ( m_maxValue - m_minValue ) / 100 );
}
