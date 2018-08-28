#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "WaveSpawner.h"
#include "WaveDisplay.h"
#include "TooltipManager.h"

enum ENEMY_TYPE {
    ENEMY_SQUARE = 1,
    ENEMY_TRIANGLE,
    ENEMY_CIRCLE,
    ENEMY_TRIPOD,
    ENEMY_QUATROPOD
};

class WaveManager {
public:
    bool init( Engine* game, std::string path, SDL_Rect waveBox );
    void close();
    void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update( Engine* game, float timeStep );
    void render( Engine* game );

    bool canSpawn   ();
    void sendNextWave();
    void spawnWave  ();

    void startGame  () { m_started = true; }
    void restartGame( Engine* game );
    bool isGameEnd  () { return m_gameEnd; }

    Enemy_data getData () { return m_spawnData; }
    // int typeToEnum  ( std::string type );
private:
    std::vector<Enemy_data>     m_enemyData;
    std::vector<SDL_Rect>       m_waveBoxes;
    std::vector<int>            m_enemyAmount;
    std::vector<int>            m_spawnVelocity;
    std::vector<float>          m_waveBoxesPos;
    std::vector<WaveDisplay>    m_displays;
    std::vector<WaveSpawner>    m_spawner;
    std::string m_spawnedEnemyType;     // Type of currently spawning enemies
    TooltipManager m_tpManager;
    Enemy_data  m_spawnData;            // Data structure of spawned enemy
    SDL_Rect    m_sideWaveBox;          // Box of wave box from side menu
    int         m_waveCounter;          // Counter of waves
    int         m_displayCounter;       // Counter if displays
    int         m_totalWaves;           // Total waves
    int         m_tpDisplayID;
    bool        m_gameEnd;              // If last wave was sent
    bool        m_started;              // If player has started the game
    bool        m_skipWave;             // If player wants to skip delay to next wave
};

#endif // WAVEMANAGER_H
