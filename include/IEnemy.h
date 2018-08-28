#ifndef IENEMY_H
#define IENEMY_H

#include "IEntity.h"
#include "vector"

class IEnemy : public IEntity {
public:
    IEnemy( Enemy_data data, SDL_Rect box, std::vector<SDL_Rect>& pathGrid );
    virtual ~IEnemy() {}
    virtual void update ( Engine* game, float timeStep );
    virtual void render ( Engine* game );
    void move           ( float timeStep );
    void dealDamage     ( float damage );
    void slow           ( float percentile, float duration );
    void renderHealth   ( Engine* game );  // Render health bar
    Enemy_data getData  () { return m_data; }
    SDL_Rect* getBox    () { return &m_box; }
    float getTravelDistance() { return m_distanceTraveled; }
    bool isDead         () { return m_dead; }
    bool isFinished     () { return m_finished; }
protected:
    std::vector<SDL_Rect> m_pathGrid;       // Vector of all path blocks loaded from file
    Enemy_data  m_data;                     // Data structure of the enemy
    SDL_Rect    m_box;                      // Rectangle of enemy
    SDL_Rect    m_maximumHealthBar;         // Rectangle of healthbar ( width is equal to m_box.w, rest is set by default )
    SDL_Rect    m_currentHealthBar;         // Rectangle of healthbar ( width is equal to m_box.w, rest is set by default )
    SDL_Point   m_prevPosition;             // Last waypoint position -> used in determinaning direction of movement towards next WP
    float       m_xPosition, m_yPosition;   // Current position
    float       m_slowDutaion;
    float       m_slowProgress;
    float       m_distanceTraveled;         // Keeps track of how far the enemy is -> used in targeting system
    int         m_movementVel;              // Speed of movement
    int         m_wpCounter;                // Waypoint counter -> tracks current waypoint
    int         m_maximumHealth;            // Maximum health of enemy
    int         m_currentHealth;            // current health of enemy
    int         m_slowMovementVel;
    bool        m_dead;
    bool        m_finished;
    bool        m_slowed;
    bool        m_velFixed;

};

#endif // IENEMY_H
