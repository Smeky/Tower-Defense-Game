#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include "IButton.h"

class ButtonMenu : public IButton {
public:
    ButtonMenu( std::string text_name, int x, int y, int w, int h, int id, SDL_Keycode hotkey = 0 );

    void update( Engine* game, float timeStep );
    void render( Engine* game );
private:
    std::string m_text;
};

#endif // BUTTONMENU_H
