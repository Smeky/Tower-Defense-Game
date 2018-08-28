#ifndef MENUMAIN_H
#define MENUMAIN_H

#include "IButton.h"
#include "TooltipManager.h"

class MenuState;

class MenuMain {
public:
    void init( Engine* game );
    void close();

    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition );
    void update( Engine* game, MenuState* state, float timeStep );
    void render( Engine* game );
private:
    void handleClick( Engine* game, MenuState* state, int id );

    std::vector<IButton*> m_buttons;

    TooltipManager m_tooltipManager;

    SDL_Rect m_centerBox;
    SDL_Rect m_temporaryBox;
};

#endif // MENUMAIN_H
