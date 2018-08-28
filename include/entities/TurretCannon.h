#ifndef TURRETCANNON_H
#define TURRETCANNON_H

#include "Engine.h"

class TurretCannon {
public:
    TurretCannon( Engine* game, std::string texture, SDL_Rect turretBox );

    void update( Engine* game, SDL_Rect turretBox, SDL_Rect targetBox );
    void render( Engine* game );

    SDL_Rect getBox () { return m_box; }
private:
    std::string m_texture;
    SDL_Rect    m_box;
    float       m_angle;
};

#endif // TURRETCANNON_H
