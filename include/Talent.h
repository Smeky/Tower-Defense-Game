#ifndef TALENT_H
#define TALENT_H

#include "IButton.h"

class Talent : public IButton {
public:
    Talent( std::string icon, SDL_Rect box, SDL_Rect bgClip, int id, bool locked, bool used );
    void render     ( Engine* game );
    bool isLocked   () { return m_locked; }
    bool isUsed     () { return m_used; }
private:
    bool        m_locked;
    bool        m_used;
    SDL_Rect    m_bgClip;
};

#endif // TALENT_H
