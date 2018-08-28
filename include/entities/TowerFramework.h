#ifndef TOWERFRAMEWORK_H
#define TOWERFRAMEWORK_H

#include "IEnemy.h"
#include "TurretCannon.h"
#include "FireEffect.h"

class IAttack;

class TowerFramework : public IEntity {
public:
    TowerFramework( Engine* game, Tower_data data, SDL_Rect box, int blockID );
    virtual ~TowerFramework();

    void update( Engine* game, float timeStep );
    void render( Engine* game );
    void renderCannon( Engine* game );

    void setAttack      ( IAttack* attack ) { m_attack = attack; }
    void setEnemies     ( std::vector<IEnemy*> &enemies ) { m_enemies = &enemies; };
    void findTarget     ( Engine* game, std::vector<IEnemy*> &enemies );
    void lockTarget     ( IEnemy* enemy );
    void freeTarget     ();
    void sellTower      () { m_isSold = true; }
    void upgradeTower   ( Tower_data data );
    void finishUpgrade  ( Engine* game );
    void resetUpgrade   () { m_isUpgrade = false; }

    std::vector<IEnemy*> &getEnemies() { return *m_enemies; }
    IAttack*    getAttack       () { return m_attack; }
    Tower_data  getData         () { return m_data; }
    Tower_data  getUpgradeData  () { return m_upgradeData; }
    SDL_Rect*   getBodyBox      () { return &m_bodyBox; }
    IEnemy*     getEnemy        () { return m_enemy; }
    int         getDamage       () { return m_data.dmg; }
    int         getRange        () { return m_data.range; }
    int         getFreezeDur    () { return m_data.freezeDur; }
    int         getSlowDur      () { return m_data.slowDur; }
    int         getSlowPwr      () { return m_data.slowPwr; }
    int         getBlockID      () { return m_blockID; }

    bool        isTargetLocked  () { return m_targetLocked; }
    bool        canFire         () { return m_canFire; }
    bool        isSold          () { return m_isSold; }
    bool        isUpgrade       () { return m_isUpgrade; }
    bool        hasProject      () { return m_hasProject; }
private:
    std::vector<IEnemy*> *m_enemies;
    TurretCannon* m_cannon;
    IAttack*    m_attack;
    Tower_data  m_data;
    Tower_data  m_upgradeData;
    SDL_Rect    m_bodyBox;
    IEnemy*     m_enemy;
    int         m_blockID;
    float       m_fireCooldown;
    float       m_fireCooldownProgress;
    bool        m_targetLocked;
    bool        m_canFire;
    bool        m_isSold;
    bool        m_isUpgrade;
    bool        m_hasProject;
};

#endif // TOWERFRAMEWORK_H
