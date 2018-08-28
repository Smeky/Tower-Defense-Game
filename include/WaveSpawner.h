#ifndef WAVESPAWNER_H
#define WAVESPAWNER_H

#include "Engine.h"

class WaveSpawner {
public:
    WaveSpawner( Enemy_data data, int amount, int velocity );

    void update         ( float timeStep );
    bool spawnEnemy     ();

    Enemy_data getData  () { return m_enemyData; }
    bool isDone         () { return m_done; }
private:
    Enemy_data  m_enemyData;
    float       m_cooldown;
    int         m_amount;
    int         m_velocity;
    int         m_counter;
    bool        m_canSpawn;
    bool        m_done;
};

#endif // WAVESPAWNER_H
