#include "WaveSpawner.h"

#include "iostream"
using namespace std;

WaveSpawner::WaveSpawner( Enemy_data data, int amount, int velocity ) {
    m_enemyData = data;         // Data structure of enemy ( texture, sound, speed, etc. )
    m_amount    = amount;       // Amount of enemies
    m_velocity  = velocity;     // Velocity between seding enemies

    m_counter   = 0;            // Counter of enemies -> used to send specific amount of them
    m_cooldown  = 0.0;          // Delay between seding enemies
    m_canSpawn  = true;         // If enemy can spawn ( Delay is large enough )
    m_done      = false;        // If last enemy was sent
}

void WaveSpawner::update( float timeStep ) {
    // Progress of delay between spawning enemies
    m_cooldown += m_velocity * timeStep;

    // If Delay is large enough, let the enemy spawn
    // and reset cooldown
    if( m_cooldown >= 20.0 ) {
        m_canSpawn = true;
        m_cooldown = 0.0;
    }
}

bool WaveSpawner::spawnEnemy() {
    // If enemy can be spawned iterate counter and
    // check if the last enemy was spawned
    if( m_canSpawn ) {
        m_counter++;

        m_canSpawn = false;

        if( m_counter == m_amount ) {
            m_done = true;
        }

        return true;
    }
    else return false;
}
