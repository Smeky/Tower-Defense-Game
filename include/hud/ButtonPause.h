#ifndef BUTTONPAUSE_H
#define BUTTONPAUSE_H

#include "IButton.h"

class ButtonPause : public IButton {
public:
    ButtonPause( int x, int y, int w, int h, int id );

    void update( Engine* game );
    void render( Engine* game );
};

#endif // BUTTONPAUSE_H
