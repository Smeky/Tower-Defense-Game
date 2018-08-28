#ifndef BUTTONLEVEL_H
#define BUTTONLEVEL_H

#include "IButton.h"

class ButtonLevel : public IButton {
public:
    ButtonLevel( SDL_Rect box, int id, bool unlocked, bool defeated );

    void update( Engine* game, float timeStep );
    void render( Engine* game );

    bool isUnlocked() { return m_unlocked; }
    bool isDefeated() { return m_defeated; }
private:
    SDL_Rect    m_lightBox;
    bool        m_unlocked;
    bool        m_defeated;
};

#endif // BUTTONLEVEL_H
