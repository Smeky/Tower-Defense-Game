#include "LevelManager.h"
#include "PlayState.h"

#include "iostream"
using namespace std;

typedef std::vector<ButtonLevel*> _lvNodes;

enum level_nodes {
    level_1 = 1,
    level_2,
    level_3,
    level_4,
    level_5,
    level_6,
    level_7,
    level_8,
    level_9,
    level_10,
};

void LevelManager::init( Engine* game, SDL_Rect bgBox ) {
    m_playLevel = false;

    vector<Level_data> levelData = *game->Saves()->getLevelData();

    m_lvNodes.push_back( new ButtonLevel( { bgBox.x + 20, bgBox.y + bgBox.h / 2,        30, 30 },
                                          level_1, levelData[ 0 ].unlocked, levelData[ 0 ].defeated ) );
    m_lvNodes.push_back( new ButtonLevel( { bgBox.x + 60, bgBox.y + bgBox.h / 2 - 30,   30, 30 },
                                          level_2, levelData[ 1 ].unlocked, levelData[ 1 ].defeated ) );
    m_lvNodes.push_back( new ButtonLevel( { bgBox.x + 60, bgBox.y + bgBox.h / 2 + 30,   30, 30 },
                                          level_3, levelData[ 2 ].unlocked, levelData[ 2 ].defeated ) );
}

void LevelManager::close() {
    while( !m_lvNodes.empty() ) delete m_lvNodes.back(), m_lvNodes.pop_back();
}

void LevelManager::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    for( _lvNodes::iterator it = m_lvNodes.begin(); it != m_lvNodes.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePos );
    }
}

void LevelManager::update( Engine* game, float timeStep ) {
    if( m_playLevel ) {
        game->setNewLevel( m_lvData );
        game->changeState( PlayState::instance() );
    }
    else {
        for( _lvNodes::iterator it = m_lvNodes.begin(); it != m_lvNodes.end(); it++ ) {
            if( (*it)->isClicked() ) {
                if( (*it)->isUnlocked() ) {
                    handleClick( game, (*it)->getID() );
                }
            }

            (*it)->update( game, timeStep );
        }
    }
}

void LevelManager::render( Engine* game ) {
    for( _lvNodes::iterator it = m_lvNodes.begin(); it != m_lvNodes.end(); it++ ) {
        (*it)->render( game );
    }
}

void LevelManager::handleClick( Engine* game, int id ) {
    switch( id ) {
    case level_1:   m_playLevel = true; m_lvData = game->Saves()->getLevelData( 0 ); break;
    case level_2:   m_playLevel = true; m_lvData = game->Saves()->getLevelData( 1 ); break;
    case level_3:   m_playLevel = true; m_lvData = game->Saves()->getLevelData( 2 ); break;
    }
}
