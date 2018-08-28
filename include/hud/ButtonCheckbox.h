#ifndef BUTTONCHECKBOX_H
#define BUTTONCHECKBOX_H

#include "IButton.h"

class ButtonCheckbox : public IButton {
public:
    ButtonCheckbox( SDL_Rect box, int id );
    void update( Engine* game, float timeStep );
    void render( Engine* game );
};

#endif // BUTTONCHECKBOX_H
