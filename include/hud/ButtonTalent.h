#ifndef BUTTONTALENT_H
#define BUTTONTALENT_H

#include "IButton.h"

class ButtonTalent : public IButton {
public:
    ButtonTalent( std::string icon, SDL_Rect box, int id, bool locked );
    void render( Engine* game );
private:
    bool m_isLocked;
};

#endif // BUTTONTALENT_H
