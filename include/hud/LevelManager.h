#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "ButtonLevel.h"

class LevelManager {
public:
    void init           ( Engine* game, SDL_Rect bgBox );
    void close          ();
    void handleEvents   ( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update         ( Engine* game, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick( Engine* game, int id );
    std::vector<ButtonLevel*> m_lvNodes;
    Level_data* m_lvData;
    bool        m_playLevel;
};

#endif // LEVELMANAGER_H
