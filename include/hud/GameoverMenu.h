#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "IGameState.h"
#include "IButton.h"

class GameoverMenu {
public:
    void init( Engine* game );
    void close();

    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition );
    void update( Engine* game, IGameState* state, float timeStep );
    void render( Engine* game );
private:
    void handleClick( Engine* game, IGameState* state, int id );
    std::vector<IButton*> m_buttons;

    SDL_Rect    m_bgBox;
    SDL_Rect    m_inBox;
    SDL_Rect    m_gameoverBox;
    bool        m_stateChange;
};

#endif // GAMEOVERMENU_H
