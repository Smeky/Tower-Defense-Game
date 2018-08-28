#ifndef BUTTONICON_H
#define BUTTONICON_H

#include "IButton.h"

class ButtonIcon : public IButton {
public:
    ButtonIcon( std::string icon, SDL_Rect box, SDL_Keycode hotkey, int id );
    void update( Engine* game, float timeStep );
    void render( Engine* game );
    void setPosition( int x, int y );
private:
    std::string m_icon;
};

#endif // BUTTONICON_H
