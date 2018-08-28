#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "IGameState.h"
#include "IButton.h"

class PauseMenu {
public:
    void init( Engine* game );
    void close();

    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition );
    void update( Engine* game, IGameState* state, float timeStep );
    void render( Engine* game );
private:
    void handleClick( Engine* game, IGameState* state, int id );

    SDL_Rect m_bgBox;
    SDL_Rect m_inBox;

    bool m_stateEnd;

    std::vector<IButton*> m_buttons;
};

#endif // PAUSEMENU_H
