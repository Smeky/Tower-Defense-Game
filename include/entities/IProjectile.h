#ifndef IPROJECTILE_H
#define IPROJECTILE_H

#include "IAttack.h"
#include "IEnemy.h"
#include "TowerFramework.h"

class IProjectile : public IEntity {
public:
    IProjectile( Projectile_data data, TowerFramework* turret, IAttack* attack );
    virtual ~IProjectile();

    void update     ( Engine* game, float timeStep );
    void render     ( Engine* game );

    SDL_Rect* getBox() { return &m_box; }
    bool isDespawn  () { return m_despawn; }
private:
    Projectile_data m_data;
    TowerFramework* m_turret;
    IEnemy*         m_enemy;
    IAttack*        m_attack;
    SDL_Rect        m_box;
    SDL_Rect        m_destBox;
    int             m_fixedVel;
    float           m_xPos;
    float           m_yPos;
    float           m_angle;
    bool            m_despawn;
    bool            m_velFixed;
    bool            m_enemyDied;
};

#endif // IPROJECTILE_H
