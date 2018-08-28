#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "IGameState.h"
#include "core/Timer.h"
#include "core/Level.h"
#include "WaveManager.h"
#include "AttackManager.h"

#include "IEnemy.h"
#include "ITower.h"
#include "entities/IProjectile.h"
#include "entities/TowerFramework.h"

#include "hud/SideMenu.h"
#include "hud/PauseMenu.h"
#include "hud/GameoverMenu.h"
#include "hud/TrackerMoney.h"
#include "hud/TrackerHealth.h"
#include "hud/TooltipManager.h"
#include "hud/TargetTower.h"

class PlayState : public IGameState {
public:
    void init( Engine* game );
    void close();

    void pause();
    void resume();

    void restart( Engine* game );

    void handleEvents( Engine* game, SDL_Event event );
    void update( Engine* game );
    void render( Engine* game );

    void sendWave();

    static PlayState* instance() { return &m_PlayState; }
private:
    static PlayState m_PlayState;
    struct GridBlock {
        SDL_Rect box;
        bool     isTaken;
    };

    bool spawnTower     ( Engine* game, Tower_data data, SDL_Rect box, int blockID );
    void spawnProjectile( Engine* game, TowerFramework* tower );
    void gameOver       ();

    std::vector<IEnemy*>            m_enemies;
    std::vector<TowerFramework*>    m_towers;
    std::vector<IProjectile*>       m_projectiles;
    std::vector<SDL_Rect>           m_levelGrid;
    std::vector<SDL_Rect>           m_pathGrid;
    std::vector<bool>               m_gridBlockTaken;
    std::vector<GridBlock>          m_gridBlock;
    TrackerHealth   m_health;
    TrackerMoney    m_money;
    TooltipManager  m_tooltipManager;
    GameoverMenu    m_gameoverMenu;
    WaveManager     m_waveManager;
    AttackManager   m_attManager;
    Level_data* m_lvData;
    Level       m_level;
    Timer       timer;
    PauseMenu   m_pauseMenu;
    SideMenu    m_sideMenu;
    TargetTower m_towerTarget;
    SDL_Rect    m_gridField;
    SDL_Rect    m_mouseoverBox;
    int         m_frameCounter;
    int         m_experience;
    float       m_timeCounter;
    bool        m_alive;
    bool        m_mouseoverGridTaken;
    bool        m_drawMouseoverBlock;
    bool        m_mousebuttonDown;
    bool        m_paused;
    bool        m_gameover;
    bool        m_shiftPressed;
};

#endif // PLAYSTATE_H
