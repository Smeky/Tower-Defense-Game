#include "hud\TargetTower.h"
#include "PlayState.h"
#include "math.h"

#include "iostream"
using namespace std;

enum BUTTON_ID {
    BUTTON_SELL = 1,
    BUTTON_TOWER_1,
    BUTTON_TOWER_2,
};

void TargetTower::targetTower( Engine* game, TowerFramework* tower ) {
    freeTarget();

    m_tower = tower;

    m_buttonID   = 0;
    m_tpButtonID = 0;

    int x = m_tower->getBodyBox()->x + m_tower->getBodyBox()->w / 2;
    int y = m_tower->getBodyBox()->y + m_tower->getBodyBox()->h / 2;
    float radius = game->calcByResW( 50 );
    float angle = 90 * ( M_PI / 180 );

    int newX = (int)( cos( angle ) * ( x - radius - x ) + x );
    int newY = (int)( sin( angle ) * ( x - radius - x ) + y );

    if( y - radius < 0 ) {
        angle += 180 * ( M_PI / 180 );

        newX = (int)( cos( angle ) * ( x - radius - x ) + x );
        newY = (int)( sin( angle ) * ( x - radius - x ) + y );

    }
    else if( x - radius < 0 ) {
        angle += 180 * ( M_PI / 180 );

        newX = (int)( cos( angle ) * ( x - radius - x ) + x );
        newY = (int)( sin( angle ) * ( x - radius - x ) + y );
    }

    if( m_tower->getData().upgrade1 != "no_upgrade" ) {
        m_buttons.push_back( ButtonIcon( game->Resources().getTowerData( m_tower->getData().upgrade1 ).tex_button, {
                                         newX, newY, (int)game->calcByResW( 25 ), (int)game->calcByResH( 25 ) },
                                         SDLK_q, BUTTON_TOWER_1 ) );

        angle -= 45 * ( M_PI / 180 );
        newX = (int)( cos( angle ) * ( x - radius - x ) + x );
        newY = (int)( sin( angle ) * ( x - radius - x ) + y );
    }
    if( m_tower->getData().upgrade2 != "no_upgrade" ) {
        m_buttons.push_back( ButtonIcon( game->Resources().getTowerData( m_tower->getData().upgrade2 ).tex_button, {
                                         newX, newY, (int)game->calcByResW( 25 ), (int)game->calcByResH( 25 ) },
                                         SDLK_w, BUTTON_TOWER_2 ) );

        angle -= 45 * ( M_PI / 180 );
        newX = (int)( cos( angle ) * ( x - radius - x ) + x );
        newY = (int)( sin( angle ) * ( x - radius - x ) + y );
    }

    m_buttons.push_back( ButtonIcon( "ICON_SELL", {
                                     newX, newY, (int)game->calcByResW( 25 ), (int)game->calcByResH( 25 ) },
                                     SDLK_s, BUTTON_SELL ) );
}

void TargetTower::freeTarget() {
    if( m_tower != NULL ) {
        m_tower = NULL;
        m_buttons.clear();
    }
}

void TargetTower::handleEvents( Engine* game, PlayState* state, SDL_Event event, SDL_Point mousePosition ) {
    m_wasEvent   = false;

    if( m_tower != NULL ) {
        for( vector<ButtonIcon>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
            it->handleEvents( game, event, mousePosition );

            if( it->isPressed() || it->isClicked() ) {
                m_buttonID = it->getID();
                m_wasEvent = true;
            }
        }

        if( m_buttonID != 0 ) {
            handleClick( game, m_buttonID );
        }
    }
}

void TargetTower::update( Engine* game ) {
    bool isMouseover = false;


    if( m_tower->isSold() ) {
        freeTarget();
    }

    for( vector<ButtonIcon>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        it->update( game, game->getTimeDelta() );

        if( it->isMouseover() ) {
            if( it->getID() != m_tpButtonID ) {
                switch( it->getID() ) {
                case BUTTON_TOWER_1:
                    m_tooltipManager.createTooltipDescription( game, game->Resources().getTowerData( m_tower->getData().upgrade1 ),
                                                               it->getBox().x - 5, it->getBox().y + it->getBox().h / 2 );

                    m_tpButtonID  = it->getID();
                    break;
                case BUTTON_TOWER_2:
                    m_tooltipManager.createTooltipDescription( game, game->Resources().getTowerData( m_tower->getData().upgrade2 ),
                                                               it->getBox().x - 5, it->getBox().y + it->getBox().h / 2 );

                    m_tpButtonID  = it->getID();
                    break;
                }
            }

            isMouseover = true;
        }
    }

    if( !isMouseover ) {
        m_tooltipManager.closeDescription();
        m_tpButtonID = 0;
    }

    m_tooltipManager.update( game );
}

void TargetTower::render( Engine* game ) {
    if( m_tower != NULL ) {
        game->DrawRadius( m_tower->getData().range,
                          m_tower->getBodyBox()->x + m_tower->getBodyBox()->w / 2,
                          m_tower->getBodyBox()->y + m_tower->getBodyBox()->h / 2 );

        for( vector<ButtonIcon>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
            it->render( game );
        }
    }

    m_tooltipManager.render( game );
}

void TargetTower::handleClick( Engine* game, int id ) {
    switch( id ) {
    case BUTTON_SELL:
        m_tower->sellTower();

        break;
    case BUTTON_TOWER_1:
        if( m_tower->getData().upgrade1 != "no_upgrade" ) {
            m_tower->upgradeTower( game->Resources().getTowerData( m_tower->getData().upgrade1 ) );
        }

        break;
    case BUTTON_TOWER_2:
        if( m_tower->getData().upgrade2 != "no_upgrade" ) {
            m_tower->upgradeTower( game->Resources().getTowerData( m_tower->getData().upgrade2 ) );
        }

        break;
    }

    game->playSound( "UI_BUTTON_PRESS" );
    freeTarget();
}
