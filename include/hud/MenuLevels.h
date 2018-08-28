#ifndef MENULEVELS_H
#define MENULEVELS_H

#include "IButton.h"
#include "hud\TooltipManager.h"

class MenuState;

class MenuLevels {
public:
    void init( Engine* game );
    void close();

    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition );
    void update( Engine* game, MenuState* state, float timeStep );
    void render( Engine* game );

    bool isStateEnd() { return m_stateEnd; }
private:
    void handleClick( Engine* game, MenuState* state, int id );
    SDL_Rect m_backgroundBox;
    std::vector<IButton*> m_buttons;

    std::string m_levelPath;

    TooltipManager m_tooltipManager;

    bool m_stateEnd;
};

#endif // MENULEVELS_H
