#ifndef PROJECTILEBEAM_H
#define PROJECTILEBEAM_H

#include "IProjectile.h"

class ProjectileBeam : public IProjectile {
public:
    ProjectileBeam( TowerFramework* tower, IAttack* attack );
    void move( Engine* game, float timeStep ) {}
    void update( Engine* game, float timeStep );
    void checkHit( Engine* game ) {}
    void render( Engine* game );
private:
    SDL_Rect m_lightBox;
    SDL_Rect m_headBox;
    float m_angle;
    float m_distance;
};

#endif // PROJECTILEBEAM_H
