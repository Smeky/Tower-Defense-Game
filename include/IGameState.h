#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include "core\Engine.h"

class IGameState {
public:
    virtual void init( Engine* game ) {}
    virtual void init( Engine* game, std::string path ) {}
    virtual void close() = 0;

    virtual void pause() {}
    virtual void resume() {}
    virtual void restart( Engine* game ) {}

    virtual void handleEvents( Engine* game, SDL_Event event ) = 0;
    virtual void update( Engine* game ) = 0;
    virtual void render( Engine* game ) = 0;

    bool isPaused() { return m_paused; }

    void changeState( Engine* game, IGameState* state ) { game->changeState( state ); }
protected:
    IGameState() {}

    bool m_paused;
};

#include "IGameState.inl"
#endif // IGAMESTATE_H
