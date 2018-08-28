#ifndef BUTTONMENUPAGE_H
#define BUTTONMENUPAGE_H

#include "IButton.h"

class ButtonMenuPage : public IButton {
public:
    ButtonMenuPage( std::string text, SDL_Rect box, int id, SDL_Keycode hotkey = 0 );
    void render( Engine* game );
private:
    std::string m_text;
};

#endif // BUTTONMENUPAGE_H
