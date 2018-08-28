#ifndef BUTTONNEXTWAVE_H
#define BUTTONNEXTWAVE_H

#include "IButton.h"

class ButtonNextwave : public IButton  {
public:
    ButtonNextwave( int x, int y, int w, int h, int id );

    void update( Engine* game, float timeStep );
    void render( Engine* game );
};

#endif // BUTTONNEXTWAVE_H
