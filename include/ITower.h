#ifndef ITOWER_H
#define ITOWER_H

#include "IEntity.h"
#include "IEnemy.h"

class ITower : public IEntity {
public:
    virtual ~ITower() {}
    virtual void update( Engine* game, float timeStep ) {};
    virtual void render( Engine* game );
    virtual void playSound( Engine* game ) {};

    void setFireCooldown( float timeStep );             // Calculates fire rate and determine if can fire or not
    void lockTarget     ( IEnemy* enemy );              // Targets the enemy and stores pointer to it
    void freeTarget     ();                             // Untargets the enemy and delete pointer to it
    void fired          () { m_fireCooldownProgress = 0.0; }    // Resets delay between shots
    void setCannonAngle ( Engine* game );               // Calculates angle of cannon
    void setSell        () { m_sell = true; }           // Let the tower be sold
    void setUpgrade     ( int type );                   // Let the tower be upgraded
    void resetUpgrade   ();                             // Stops the upgrade
    SDL_Rect* getBox    () { return &m_box; }           // Returns pointer to tower rect
    SDL_Rect* getCannonBox() { return &m_cannonBox; }   // Returns pointer to cannon rect
    IEnemy* getTarget   () { return m_enemy; }          // Returns pointer to targeted enemy
    int* getDamage       () { return &m_damage; }        // Returns pointer to tower damage <- used by projectile on target hit
    int getFireRange    () { return m_fireRadius; }     // Returns tower fire radius
    int getPrice        () { return m_price; }          // Returns tower price
    int getType         () { return m_type; }           // Returns type of tower <- from enum
    int getUpgradeType  () { return m_upgradeType; }    // Returns type of upgrade tower
    float getBlastDamage() { return m_blastDamage; }    // Returns AoE tower damage
    bool canFire        ( Engine* game );               // Determine if shooting at the enemy is possible, otherwise waits or frees target
    bool isInDistance   ( Engine* game );               // Determine if enemy is in fire range
    bool isTargetLocked () { return m_targetLocked; }   // Returns if target is locked
    bool isSell         () { return m_sell; }           // Returns if tower should be sold
    bool isUpgrade      () { return m_upgrade; }        // Returns true if tower is upgraded
protected:
    ITower( SDL_Rect box, int type );
    std::string m_text;            // Address to tower base texture
    std::string m_cannonText;      // Address to cannon texture
    SDL_Rect m_box;                // Towers base rect
    SDL_Rect m_cannonBox;          // Cannons rect
    IEnemy* m_enemy;               // Pointer to targeted enemy
    int m_type;                    // Type of tower <- from enum
    int m_upgradeType;             // Type of tower that should be upgraded to
    int m_fireRadius;              // Towers shoot radius
    int m_damage;                  // Towers damage
    int m_price;                   // Towers price
    int m_fireVelocity;            // Velocity of delay between shooting
    float m_blastDamage;           // Towers AoE damage
    float m_fireCooldown;          // Shoot Delay
    float m_fireCooldownProgress;  // Delay progress
    float m_cannonAngle;           // Angle of cannon
    bool m_targetLocked;           // If target is locked
    bool m_canFire;                // If can fire
    bool m_sell;                   // If the tower should be sold
    bool m_upgrade;                // If the tower should be upgraded;
};

#endif // ITOWER_H
