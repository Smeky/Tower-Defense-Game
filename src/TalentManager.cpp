#include "TalentManager.h"

#include "iostream"
using namespace std;

typedef std::vector<Talent> _talent;

enum talent_id {
    talent_id_1 = 1,
    talent_id_2,
    talent_id_3,
    talent_id_4,
    talent_id_5,
    talent_id_6,
    talent_id_7,
};

void TalentManager::init( Engine* game, SDL_Rect menuBox ) {
    SDL_Rect tlPlasmaBox;
    tlPlasmaBox.x = menuBox.x;
    tlPlasmaBox.y = menuBox.y + 50;
    tlPlasmaBox.w = 155;
    tlPlasmaBox.h = menuBox.h - 50;

    SDL_Rect tlBgClip = { 0, 0, game->getTextureW( "GUI_ICON_TALENT_BG" ), game->getTextureH( "GUI_ICON_TALENT_BG" ) / 5 };

    m_talents.push_back( Talent( "GUI_ICON_TALENT_PLASMA_DMGUP",
                                 { tlPlasmaBox.x + tlPlasmaBox.w / 2, tlPlasmaBox.y + 50, 40, 40 },
                                 tlBgClip, talent_id_1, false, false ) );
}

void TalentManager::close() {
    m_talents.clear();
}

void TalentManager::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePos ) {
    for( _talent::iterator it = m_talents.begin(); it != m_talents.end(); it++ ) {
        it->handleEvents( game, event, mousePos );
    }
}

void TalentManager::update( Engine* game, float timeStep ) {
    for( _talent::iterator it = m_talents.begin(); it != m_talents.end(); it++ ) {
        if( it->isClicked() ) {
            handleClick( game, it->getID() );
        }

        it->update( game, timeStep );
    }
}

void TalentManager::render( Engine* game ) {
    for( _talent::iterator it = m_talents.begin(); it != m_talents.end(); it++ ) {
        it->render( game );
    }
}

void TalentManager::handleClick( Engine* game, int id ) {
    switch( id ) {
    case talent_id_1: break;
    case talent_id_2: break;
    case talent_id_3: break;
    case talent_id_4: break;
    case talent_id_5: break;
    case talent_id_6: break;
    case talent_id_7: break;
    default: break;
    }
}
