#ifndef MENUPAGE_H
#define MENUPAGE_H

#include "IButton.h"

class MenuPage {
public:
    virtual void init           ( Engine* game, SDL_Rect box ) {}
    virtual void close          ();
    virtual void handleEvents   ( Engine* game, SDL_Event event, SDL_Point mousePos );
    virtual void update         ( Engine* game, float timeStep );
    virtual void render         ( Engine* game );
protected:
    std::vector<IButton*> m_buttons;
    SDL_Rect m_bgBox;
};

#endif // MENUPAGE_H
