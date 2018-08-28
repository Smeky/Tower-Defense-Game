#include "PlayState.h"

#include "algorithm"
#include "math.h"
#include "sstream"

#include "IAttack.h"

#include "iostream"
using namespace std;

typedef std::vector<IProjectile*> _projectile;

PlayState PlayState::m_PlayState;

void PlayState::init( Engine* game ) {
    m_lvData = game->getNewLevel();

    // Load and build level from xml file
    m_level.loadLevelFromFile( m_lvData->path, game );

    // Store whole grid ( size is loaded from file ) -> used for towers and mouseover checking
    m_levelGrid = m_level.getGrid();

    for( int i = 0; i < (int)m_levelGrid.size(); i++ ) {
        m_gridBlock.push_back( GridBlock() );
        m_gridBlock.back().box      = m_levelGrid[ i ];
        m_gridBlock.back().isTaken  = false;
    }

    // Store path blocks ( loaded from file ) -> used for enemies to move by the path
    m_pathGrid = m_level.getPathgrid();

    // Determine if grid blocks are free for building or not
    for( int i = 0; i < (int)m_levelGrid.size(); i++ ) {

        for( int j = 0; j < (int)m_pathGrid.size(); j++ ) {
            if( j == 1 ) {
                if( m_pathGrid[ j ].x == m_levelGrid[ i ].x + 1 && m_pathGrid[ j ].y == m_levelGrid[ i ].y ) {

                    m_gridBlock[ i ].isTaken = true;
                    j = (int)m_levelGrid.size();
                }
            }
            else {
                if( m_pathGrid[ j ].x == m_levelGrid[ i ].x && m_pathGrid[ j ].y == m_levelGrid[ i ].y ) {

                    m_gridBlock[ i ].isTaken = true;
                    j = (int)m_levelGrid.size();
                }
            }
        }
    }

    m_mouseoverGridTaken = false;
    m_drawMouseoverBlock = false;

    m_money.init( game, 12000 );
    m_health.init( game, 20 );
    m_alive = true;

    m_frameCounter = 0;
    m_timeCounter  = 0;

    m_sideMenu.init( game, m_level.getMapWidth(), m_level.getMapHeight() );

    // Load waves
    m_waveManager.init( game, m_level.getWavePath(), m_sideMenu.getWaveBox() );

    m_paused = false;
    m_pauseMenu.init( game );

    m_gameover = false;
    m_gameoverMenu.init( game );

    m_shiftPressed  = false;
    m_experience    = 0;
}

void PlayState::close() {
    m_towerTarget.freeTarget();

    m_level.close();
    m_sideMenu.close();
    m_pauseMenu.close();
    m_waveManager.close();
    m_tooltipManager.close();
    m_gameoverMenu.close();

    m_pathGrid.clear();
    m_levelGrid.clear();
    m_gridBlock.clear();

    while( !m_towers.empty()      ) delete m_towers.back(),      m_towers.pop_back();
    while( !m_projectiles.empty() ) delete m_projectiles.back(), m_projectiles.pop_back();
    while( !m_enemies.empty()     ) delete m_enemies.back(),     m_enemies.pop_back();
}

void PlayState::pause() {
    m_paused = true;

    timer.stop();
}

void PlayState::resume() {
    m_paused = false;

    timer.start();
}

void PlayState::gameOver() {
    timer.stop();
    m_gameover = true;
}

void PlayState::restart( Engine* game ) {
    m_money.reset( game );
    m_health.reset( game );

    m_tooltipManager.close();

    m_alive = true;
    m_gameover = false;

    while( !m_towers.empty()      ) delete m_towers.back(),      m_towers.pop_back();
    while( !m_enemies.empty()     ) delete m_enemies.back(),     m_enemies.pop_back();
    while( !m_projectiles.empty() ) delete m_projectiles.back(), m_projectiles.pop_back();

    // Determine if grid blocks are free for building or not
    for( int i = 0; i < (int)m_gridBlock.size(); i++ ) {
        m_gridBlock[ i ].isTaken = false;

        for( int j = 0; j < (int)m_pathGrid.size(); j++ ) {
            if( m_pathGrid[ j ].x == m_gridBlock[ i ].box.x && m_pathGrid[ j ].y == m_gridBlock[ i ].box.y ) {

                m_gridBlock[ i ].isTaken = true;
                j = (int)m_gridBlock.size();
            }
        }
    }

    m_waveManager.restartGame( game );

    resume();
}

void PlayState::handleEvents( Engine* game, SDL_Event event ) {
    SDL_Point mousePosition;

    // Store mouse x/y position
    SDL_GetMouseState( &mousePosition.x, &mousePosition.y );

    if( m_paused ) {
        m_pauseMenu.handleEvents( game, event, mousePosition );
    }
    else if( m_gameover ) {
        m_gameoverMenu.handleEvents( game, event, mousePosition );
    }
    else {
        m_sideMenu.handleEvents( game, event, mousePosition );
        m_towerTarget.handleEvents( game, this, event, mousePosition );
        m_waveManager.handleEvents( game, event, mousePosition );

        if( m_sideMenu.getClickedTower() != 0 ) {
            m_towerTarget.freeTarget();
        }

        if( m_sideMenu.getClickedTower() != 0 ) {
            for( int i = 0; i < (int)m_gridBlock.size(); i++ ) {

                if( game->checkMouseover( mousePosition, &m_gridBlock[ i ].box ) ) {

                    m_mouseoverBox = m_gridBlock[ i ].box;

                    m_drawMouseoverBlock = true;

                    if( m_gridBlock[ i ].isTaken ) {
                        m_mouseoverGridTaken = true;
                    }
                    else {
                        m_mouseoverGridTaken = false;
                    }
                }
            }
        }
        else {
            m_drawMouseoverBlock = false;
        }

        // If mousebutton was pressed
        if( event.type == SDL_MOUSEBUTTONDOWN ) {

            // If Left mouse button was pressed
            if( event.button.button == SDL_BUTTON_LEFT ) {
                for( int i = 0; i < (int)m_towers.size(); i++ ) {
                    if( game->checkMouseover( mousePosition, m_towers[ i ]->getBodyBox() ) ) {
                        if( !m_towerTarget.wasEvent() ) {
                            m_towerTarget.targetTower( game, m_towers[ i ] );

                            i = m_towers.size();

                            m_sideMenu.resetClickedTower();
                        }
                    }
                    else m_towerTarget.freeTarget();
                }


                if( !m_towerTarget.isSelected() && !m_towerTarget.wasEvent() ) {
                    for( int i = 0; i < (int)m_gridBlock.size(); i++ ) {
                        if( game->checkMouseover( mousePosition, &m_gridBlock[ i ].box ) ) {
                            if( !m_gridBlock[ i ].isTaken ) {
                                if( m_sideMenu.getClickedTower() != 0 ) {
                                    if( spawnTower( game, m_sideMenu.getTowerData(), m_mouseoverBox, i ) ) {
                                        m_gridBlock[ i ].isTaken = true;
                                        m_mouseoverGridTaken     = true;

                                        if( !m_shiftPressed ) {
                                            m_sideMenu.resetClickedTower();
                                        }
                                    }
                                }
                            }
                            else {
                                if( m_sideMenu.getClickedTower() != 0 ) {
                                    m_tooltipManager.createTooltipWarning( game, "TEXT_TOOLTIP_ERROR_BLOCK_TAKEN", 5, 5, true );
                                    game->playSound( "SOUND_UI_ERROR" );
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Keyboard events
    if( event.type == SDL_KEYDOWN ) {
        switch( event.key.keysym.sym ) {
        case SDLK_ESCAPE: game->setQuit(); break;
        case SDLK_l: m_money.init( game, 100 ); break;
        case SDLK_k: m_money.init( game, 10000 ); break;
        case SDLK_LSHIFT: m_shiftPressed = true;
        }
    }
    else if( event.type == SDL_KEYUP ) {
        switch( event.key.keysym.sym ) {
        case SDLK_LSHIFT: m_shiftPressed = false;
        }
    }
}

void PlayState::update( Engine* game ) {
    // Time delta calculation
    float timeDelta = timer.getTicks() / 1000.f;

    // Reset timer ( important for calculation delta time )
    if( !m_paused && !m_gameover ) timer.start();

//    if( m_timeCounter < 1 ) {
//        m_timeCounter += timeDelta;
//        m_frameCounter++;
//    }
//    else {
//        m_timeCounter = 0;
//        m_frameCounter = 0;
//    }

    if( !m_alive ) {
        gameOver();
    }

    m_waveManager.update( game, timeDelta );

    if( m_waveManager.isGameEnd() && m_enemies.empty() && !m_gameover ) {
        game->Saves()->getLevelData( m_lvData->id )->defeated = true;
        game->Saves()->getLevelData( m_lvData->id + 1 )->unlocked = true;
        game->Saves()->m_exp += m_experience;
        game->Saves()->saveGame();

        gameOver();
    }

    if( m_waveManager.canSpawn() ) {
        m_enemies.push_back( new IEnemy( m_waveManager.getData(), { m_pathGrid[ 0 ].x, m_pathGrid[ 0 ].y, (int)game->calcByResW( 15 ), (int)game->calcByResH( 15 ) }, m_pathGrid ) );
    }

    for( _projectile::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ) {
        (*it)->update( game, timeDelta );

        if( (*it)->isDespawn() ) {
            delete *it;
            it = m_projectiles.erase( it );
        }
        else {
            it++;
        }
    }

    // Move and update all enemies
    for( vector<IEnemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); ) {
        (*it)->update( game, timeDelta );
        (*it)->move( timeDelta );

        // If the enemy died, delete it
        if( (*it)->isDead() ) {
            delete *it;
            it = m_enemies.erase( it );

            // Add money
            m_money.add( game, 5 );

            m_experience += 5;
        }
        // If the enemy hit last waypoint, delete it
        else if( (*it)->isFinished() ) {
            delete *it;
            it = m_enemies.erase( it );

            // If the health hits zero, end game
            if( !m_health.remove( game, 1 ) ) {
                m_alive = false;
            }
        }
        else it++;
    }

    // Check if tower is sold. If so, return some money and unlock grid block
    for( vector<TowerFramework*>::iterator it = m_towers.begin(); it != m_towers.end(); ) {
        if( (*it)->isSold() ) {
            m_money.add( game, (*it)->getData().price / 2 );
            m_gridBlock[ (*it)->getBlockID() ].isTaken = false;

            delete *it;
            it = m_towers.erase( it );

            it = m_towers.end();
        }
        else {
            if( (*it)->isUpgrade() ) {
                if( m_money.remove( game, (*it)->getUpgradeData().price ) ) {
                    (*it)->finishUpgrade( game );
                }
                else {
                    (*it)->resetUpgrade();

                    m_tooltipManager.createTooltipWarningUp( game, "TEXT_TOOLTIP_NOT_ENOUGH_MONEY",
                                                             m_sideMenu.getMoneyBox().x + m_sideMenu.getMoneyBox().w / 2,
                                                             m_sideMenu.getMoneyBox().y - 20, true );
                    game->playSound( "SOUND_UI_ERROR" );
                }
            }

            it++;
        }
    }

    for( vector<TowerFramework*>::iterator it = m_towers.begin(); it != m_towers.end(); it++ ) {
        if( !(*it)->isTargetLocked() ) {
            (*it)->findTarget( game, m_enemies );
        }

        (*it)->update( game, timeDelta );

        if( (*it)->canFire() ) {
            if( (*it)->hasProject() ) {
                spawnProjectile( game, (*it) );
            }

            game->playSound( (*it)->getData().snd_attack );
        }
    }


    if( m_paused ) {
        m_pauseMenu.update( game, this, timeDelta );
    }
    else if( m_gameover ) {
        m_gameoverMenu.update( game, this, timeDelta );
    }
    else {
        m_sideMenu.update( game, this, timeDelta );
    }

    // If tower is targeted
    if( m_towerTarget.isSelected() ) {
        m_towerTarget.update( game );
    }

    m_tooltipManager.update( game );
}

void PlayState::render( Engine* game ) {
    // Render level base
    m_level.render( game );

    if( m_drawMouseoverBlock ) {
        if( m_mouseoverGridTaken ) {
            SDL_SetRenderDrawColor( game->getRenderer(), 255, 0, 0, 60 );
            SDL_RenderFillRect( game->getRenderer(), &m_mouseoverBox );
        }
        else {
            SDL_SetRenderDrawColor( game->getRenderer(), 200, 200, 200, 60 );
            SDL_RenderFillRect( game->getRenderer(), &m_mouseoverBox );
        }
    }

    // Render enemies
    for( vector<IEnemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++ ) {
        (*it)->render( game );
    }

    for( vector<TowerFramework*>::iterator it = m_towers.begin(); it != m_towers.end(); it++ ) {
        (*it)->render( game );
    }

    for( vector<TowerFramework*>::iterator it = m_towers.begin(); it != m_towers.end(); it++ ) {
        (*it)->renderCannon( game );
    }

    // Render projectiles
    for( vector<IProjectile*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++ ) {
        (*it)->render( game );
    }


    for( vector<IEnemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++ ) {
        (*it)->renderHealth( game );
    }

    // If a tower is targeted, render its radius, buttons, etc.
    if( m_towerTarget.isSelected() ) {
        m_towerTarget.render( game );
    }

    m_sideMenu.render( game );
    m_waveManager.render( game );

    m_money.render(  game, m_sideMenu.getMoneyBox().x  + game->calcByResW( 5 ), m_sideMenu.getMoneyBox().y  + m_sideMenu.getMoneyBox().h  / 2 + 1 );
    m_health.render( game, m_sideMenu.getHealthBox().x + game->calcByResW( 5 ), m_sideMenu.getHealthBox().y + m_sideMenu.getHealthBox().h / 2 + 1 );


    m_tooltipManager.render( game );

    if( m_paused ) {
        m_pauseMenu.render( game );
    }
    else if( m_gameover ) {
        m_gameoverMenu.render( game );
    }
}

void PlayState::sendWave() {
    m_waveManager.sendNextWave();
}

bool PlayState::spawnTower( Engine* game, Tower_data data, SDL_Rect box, int blockID ) {
    SDL_Rect towerRect;
    towerRect.w = (int)game->calcByResH( 33 );
    towerRect.h = (int)game->calcByResH( 33 );
    towerRect.x = box.x + ( box.w - towerRect.w ) / 2;
    towerRect.y = box.y + ( box.h - towerRect.h ) / 2;

    if( m_money.remove( game, data.price ) ) {
        m_towers.push_back( new TowerFramework( game, data, towerRect, blockID ) );

        m_towers.back()->setAttack( m_attManager.getAttack( data.ability ) );
        m_towers.back()->setEnemies( m_enemies );

        game->playSound( "TURRET_PLACEMENT" );
    }
    else {
        m_tooltipManager.createTooltipWarningUp( game, "TEXT_TOOLTIP_NOT_ENOUGH_MONEY",
                                                 m_sideMenu.getMoneyBox().x + m_sideMenu.getMoneyBox().w / 2,
                                                 m_sideMenu.getMoneyBox().y - 20, true );
        game->playSound( "SOUND_UI_ERROR" );
    }

    return true;
}

void PlayState::spawnProjectile( Engine* game, TowerFramework* tower ) {
    m_projectiles.push_back( new IProjectile( game->Resources().getProjectData( tower->getData().projectName ), tower, tower->getAttack() ) );
}
