#include "WaveManager.h"

#include "iostream"
using namespace std;

#include "core\tinyxml2.h"
using namespace tinyxml2;

bool WaveManager::init( Engine* game, std::string path, SDL_Rect waveBox ) {
    bool success = true;

    m_sideWaveBox = waveBox;

    m_waveCounter           = -1;           // Used to determine which vector index should be used
    m_tpDisplayID           = 0;
    m_totalWaves            = 0;            // Total amount of waves, used to determine game end
    m_gameEnd               = false;        // If last ( final ) wave was sent
    m_started               = false;        // Wait for player to start the game
    m_skipWave              = false;        // If player wants to skip delay( send new wave )

    XMLDocument file;

    // If the file loading failes ( usually wrong file path or missing file )
    if( file.LoadFile( path.c_str() ) != XML_NO_ERROR ) {
        cout << "Failed to initialize waves from file at: " << path << endl;
        cout << "Perhaps the file is missing in /media/data directory." << endl;
        success = false;
    }
    else {
        XMLElement* element = file.FirstChildElement( "level" );

        int displayIndex = 1;

        // Store all wave data and count total waves
        for( XMLElement* data = element->FirstChildElement(); data != NULL; data = data->NextSiblingElement() ) {
            m_enemyData.push_back( Enemy_data() );

            m_enemyData.back() = game->Resources().getEnemyData( data->Attribute( "enemy" ) );
            m_enemyData.back().health   = data->IntAttribute( "health" );

            /** FIX ME **/
            // m_enemyData.back().price = data->IntAttribute( "price" );

            m_enemyAmount.push_back( data->IntAttribute( "amount" ) );
            m_spawnVelocity.push_back( data->IntAttribute( "velocity" ) );

            m_totalWaves++;

            m_displays.push_back( WaveDisplay( game, m_enemyData.back(), m_enemyAmount.back(), waveBox, displayIndex, waveBox.y + waveBox.h - ( m_sideWaveBox.h / 10 + game->calcByResH( 10 ) ) * ( m_totalWaves ) ) );
            displayIndex++;
        }
    }

    return success;
}

void WaveManager::close() {
    m_enemyData.clear();
    m_enemyAmount.clear();
    m_spawnVelocity.clear();
    m_displays.clear();
    m_spawner.clear();
    m_tpManager.close();
}

void WaveManager::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    for( vector<WaveDisplay>::iterator it = m_displays.begin(); it != m_displays.end(); it++ ) {
        it->handleEvents( game, event, mousePos );
    }
}

void WaveManager::update( Engine* game, float timeStep ) {
    bool isMouseover = false;

    // If player started game

    // Go trough all wave displays
    for( vector<WaveDisplay>::iterator it = m_displays.begin(); it != m_displays.end(); ) {
        if( it->isMouseover() ) {
            if( it->getID() != m_tpDisplayID ) {
                m_tpManager.createTooltipDescription( game, it->getData(), it->getBox()->x - 5, it->getBox()->y + it->getBox()->h / 2 );
                m_tpDisplayID = it->getID();
            }

            isMouseover = true;
        }

        if( !m_started ) {
            it++;
        }
        else {
            // If player wants to skip to next wave
            if( m_skipWave ) {
                it->skipWave();
            }
            else {
                it->waveSkiped();
            }

            it->update( game, timeStep );

            if( it->isDone() ) {
                spawnWave();

                m_skipWave = false;

                m_displays.erase( it );
            }
            else it++;
        }
    }

    if( !isMouseover ) {
        m_tpManager.closeDescription();
        m_tpDisplayID = 0;
    }

    if( m_started ) {

        // Update all wave spawners
        // If one of them is done, erase it
        for( vector<WaveSpawner>::iterator it = m_spawner.begin(); it != m_spawner.end(); ) {
            if( it->isDone() ) {
                m_spawner.erase( it );

                if( m_waveCounter + 1 == m_totalWaves ) {
                    m_gameEnd =  true;
                }
            }
            else {
                it->update( timeStep );

                it++;
            }
        }
    }
}

void WaveManager::render( Engine* game ) {
    for( vector<WaveDisplay>::iterator it = m_displays.begin(); it != m_displays.end(); it++ ) {
        it->render( game );
    }

    m_tpManager.render( game );
}

bool WaveManager::canSpawn() {
    // Go trough all wave spawners
    for( vector<WaveSpawner>::iterator it = m_spawner.begin(); it != m_spawner.end(); it++ ) {
        // If enemy can spawn, get its data so we can return them
        if( it->spawnEnemy() ) {
            m_spawnData = it->getData();

            return true;
        }
    }

    return false;
}
void WaveManager::sendNextWave() {
    if( !m_started ) m_started = true;
    m_skipWave = true;
}

void WaveManager::spawnWave() {
    if( !m_gameEnd ) {
        m_waveCounter++;

        m_spawner.push_back( WaveSpawner( m_enemyData[ m_waveCounter ],
                                          m_enemyAmount[ m_waveCounter ],
                                          m_spawnVelocity[ m_waveCounter ] ) );
    }
}

void WaveManager::restartGame( Engine* game ) {
    // Reset everything in case of game restart
    m_waveCounter           = -1;
    m_gameEnd               = false;
    m_started               = false;
    m_skipWave              = false;

    m_spawner.clear();
    m_displays.clear();

    for( int i = 0; i < m_totalWaves; i++ ) {
        m_displays.push_back( WaveDisplay( game, m_enemyData[ i ], m_enemyAmount[ i ], m_sideWaveBox, i + 1, m_sideWaveBox.y + m_sideWaveBox.h - ( m_sideWaveBox.h / 10  + game->calcByResH( 10 ) ) * ( i + 1 ) ) );
    }
}
