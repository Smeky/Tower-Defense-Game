#include "SliderButton.h"

SliderButton::SliderButton( int x, int y, int w, int h ) : IButton( x, y, w, h, 0 ) {}

void SliderButton::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 255, 0, 0, 255 );
    SDL_RenderDrawRect( game->getRenderer(), &m_box );
}
