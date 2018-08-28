#ifndef SLIDERBUTTON_H
#define SLIDERBUTTON_H

#include "IButton.h"

class SliderButton  : public IButton {
public:
    SliderButton( int x, int y, int w, int h );
    void render( Engine* game );
};

#endif // SLIDERBUTTON_H
