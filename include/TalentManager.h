#ifndef TALENTMANAGER_H
#define TALENTMANAGER_H

#include "Talent.h"

class TalentManager {
public:
    void init( Engine* game, SDL_Rect menuBox );
    void close();
    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update( Engine* game, float timeStep );
    void render( Engine* game );
private:
    void handleClick( Engine* game, int id );
    std::vector<Talent> m_talents;
};

#endif // TALENTMANAGER_H
