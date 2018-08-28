#include "hud/SideMenu.h"

#include "PlayState.h"
#include "hud/ButtonPause.h"
#include "hud/ButtonTowerSelection.h"
#include "hud/ButtonNextwave.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> Button;
typedef std::vector<ButtonTowerSelection*> ButtonSelect;

enum BUTTON_ID {
    BUTTON_ID_TOWER_1 = TOWER_PLASMA,
    BUTTON_ID_TOWER_2 = TOWER_BEAM,
    BUTTON_ID_TOWER_3 = TOWER_SLOWER,
    BUTTON_ID_TOWER_4 = TOWER_BOMBER,
    BUTTON_ID_PAUSE,
    BUTTON_ID_NEXTWAVE,
};

void SideMenu::init( Engine* game, int gridWidth, int gridHeight ) {
    m_botBox.x = 0;
    m_botBox.y = gridHeight;
    m_botBox.w = gridWidth;
    m_botBox.h = game->getWindowH() - gridHeight;

    m_sideBox.x = gridWidth;
    m_sideBox.y = 0;
    m_sideBox.w = ( ( game->getWindowW() - gridWidth ) / 4 ) * 3 ;
    m_sideBox.h = game->getWindowH() - m_botBox.h * 1.5;

    m_waveBox.x = m_sideBox.x + m_sideBox.w;
    m_waveBox.y = 0;
    m_waveBox.w = game->getWindowW() - m_sideBox.x - m_sideBox.w;
    m_waveBox.h = m_sideBox.h;

    m_buttons.push_back( new ButtonPause( m_botBox.x + game->calcByResW( 2 ), m_botBox.y + game->calcByResH( 2 ),
                                          m_botBox.h - game->calcByResW( 2 ), m_botBox.h - game->calcByResH( 4 ), BUTTON_ID_PAUSE ) );

    m_moneyBox.x = m_buttons.back()->getBox().x + m_buttons.back()->getBox().w + 3;
    m_moneyBox.y = m_buttons.back()->getBox().y;
    m_moneyBox.w = game->calcByResW( 80 );
    m_moneyBox.h = m_buttons.back()->getBox().h + 1;

    m_healthBox.x = m_moneyBox.x + m_moneyBox.w + 2;
    m_healthBox.y = m_moneyBox.y;
    m_healthBox.w = game->calcByResW( 45 );
    m_healthBox.h = m_moneyBox.h;

    m_towSlctBut.push_back( new ButtonTowerSelection( game->Resources().getTowerData( "shooter" ), {
                                                   m_sideBox.x + 2, m_sideBox.y + 2,
                                                   m_sideBox.w - 4, m_sideBox.h / 8 },
                                                   SDLK_1, BUTTON_ID_TOWER_1 ) );

    m_towSlctBut.push_back( new ButtonTowerSelection( game->Resources().getTowerData( "beam" ), {
                                                   m_sideBox.x + 2, m_towSlctBut.back()->getBox().y + m_towSlctBut.back()->getBox().h + 1,
                                                   m_sideBox.w - 4, m_sideBox.h / 8 },
                                                   SDLK_2, BUTTON_ID_TOWER_2 ) );

    m_towSlctBut.push_back( new ButtonTowerSelection( game->Resources().getTowerData( "cooler" ), {
                                                   m_sideBox.x + 2, m_towSlctBut.back()->getBox().y + m_towSlctBut.back()->getBox().h + 1,
                                                   m_sideBox.w - 4, m_sideBox.h / 8 },
                                                   SDLK_3, BUTTON_ID_TOWER_3 ) );

    m_towSlctBut.push_back( new ButtonTowerSelection( game->Resources().getTowerData( "mortar" ), {
                                                   m_sideBox.x + 2, m_towSlctBut.back()->getBox().y + m_towSlctBut.back()->getBox().h + 1,
                                                   m_sideBox.w - 4, m_sideBox.h / 8 },
                                                   SDLK_4, BUTTON_ID_TOWER_4 ) );


    m_buttons.push_back( new ButtonNextwave(    m_sideBox.x,
                                                m_sideBox.y + m_sideBox.h,
                                                m_sideBox.w + m_waveBox.w,
                                                m_botBox.h * 1.5,
                                                BUTTON_ID_NEXTWAVE ) );

    m_selectedTower = 0;
    m_tpButtonID    = 0;
    m_sellTower     = false;
}

void SideMenu::close() {
    m_tpManager.close();

    while( !m_buttons.empty() ) delete m_buttons.back(), m_buttons.pop_back();
    while( !m_towSlctBut.empty() ) delete m_towSlctBut.back(), m_towSlctBut.pop_back();
}

void SideMenu::handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition ) {
    m_mousePos = mousePosition;

    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->handleEvents( game, event, m_mousePos );
    }

    for( ButtonSelect::iterator it = m_towSlctBut.begin(); it != m_towSlctBut.end(); it++ ) {
        (*it)->handleEvents( game, event, m_mousePos );
    }
}

void SideMenu::update( Engine* game, PlayState* state, float timeStep ) {
    bool isMouseover = false;

    // Go trough all non-tower selecting buttons
    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        if( (*it)->isClicked() ) {
            if( (*it)->getID() == m_selectedTower ) {
                m_selectedTower = 0;
            }
            else {
                handleClick( game, state, (*it)->getID() );
            }

            (*it)->setClicked( false );

        }

        (*it)->update( game, timeStep );
    }

    // Go trough all tower selecting buttons
    for( ButtonSelect::iterator it = m_towSlctBut.begin(); it != m_towSlctBut.end(); it++ ) {
        if( (*it)->isClicked() ) {
            if( (*it)->getID() == m_selectedTower ) {
                m_selectedTower = 0;
            }
            else {
                handleClick( game, state, (*it)->getID() );
            }

            (*it)->setClicked( false );

        }

        (*it)->update( game, timeStep );

        if( (*it)->isMouseover() ) {
            if( (*it)->getID() != m_tpButtonID ) {
                m_tpManager.createTooltipDescription( game, (*it)->getTowerData(),
                                                     (*it)->getBox().x - 5, (*it)->getBox().y + (*it)->getBox().h / 2 );

                m_tpButtonID = (*it)->getID();
            }

            isMouseover  = true;
        }
    }

    if( !isMouseover ) {
        m_tpManager.closeDescription();
        m_tpButtonID = 0;
    }

    m_tpManager.update( game );
}

void SideMenu::render( Engine* game ) {
    // Render bottom and side menu background
    SDL_SetRenderDrawColor( game->getRenderer(), 10, 15, 20, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_sideBox );
    SDL_RenderFillRect( game->getRenderer(), &m_botBox );

    // Render wave box background
    SDL_SetRenderDrawColor( game->getRenderer(), 0, 0, 0, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_waveBox );


    // Render Tracker boxes
    SDL_SetRenderDrawColor( game->getRenderer(), 10, 15, 20, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_moneyBox );
    SDL_RenderFillRect( game->getRenderer(), &m_healthBox );

    // Render line separating bottom and side menu from grid
    SDL_SetRenderDrawColor( game->getRenderer(), 80, 140, 190, 120 );
    SDL_RenderDrawLine( game->getRenderer(), m_botBox.x,  m_botBox.y,  m_botBox.x + m_botBox.w, m_botBox.y );
    SDL_RenderDrawLine( game->getRenderer(), m_sideBox.x, m_sideBox.y, m_sideBox.x, m_sideBox.y + m_sideBox.h );

    // Render Border for trackers
    SDL_SetRenderDrawColor( game->getRenderer(), 50, 75, 85, 120 );
    SDL_RenderDrawRect( game->getRenderer(), &m_moneyBox );
    SDL_RenderDrawRect( game->getRenderer(), &m_healthBox );

    // Render all buttons
    for( Button::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ) {
        (*it)->render( game );
    }

    for( ButtonSelect::iterator it = m_towSlctBut.begin(); it != m_towSlctBut.end(); it++ ) {
        if( m_selectedTower == (*it)->getID() ) {
            (*it)->setClicked( true );
            (*it)->render( game );
            (*it)->setClicked( false );
        }
        else (*it)->render( game );
    }

    // Render tooltips
    m_tpManager.render( game );

    // Render selected tower at mouse position
    if( m_selectedTower != 0 ) {
        game->drawTexture( m_towerData.tex_body,   m_mousePos.x, m_mousePos.y, NULL, NULL, true, true, 90 );
        game->drawTexture( m_towerData.tex_cannon, m_mousePos.x, m_mousePos.y, NULL, NULL, true, true, 90 );
    }
}

void SideMenu::handleClick( Engine* game, PlayState* state, int id ) {
    switch( id ) {
    case BUTTON_ID_TOWER_1: m_selectedTower = id; m_towerData = game->Resources().getTowerData( "shooter" ); break;
    case BUTTON_ID_TOWER_2: m_selectedTower = id; m_towerData = game->Resources().getTowerData( "beam" ); break;
    case BUTTON_ID_TOWER_3: m_selectedTower = id; m_towerData = game->Resources().getTowerData( "cooler" ); break;
    case BUTTON_ID_TOWER_4: m_selectedTower = id; m_towerData = game->Resources().getTowerData( "mortar" ); break;
    case BUTTON_ID_PAUSE: resetClickedTower(), state->pause(); break;
    case BUTTON_ID_NEXTWAVE: state->sendWave(); break;
    }
}

Tower_data SideMenu::getTowerData() {
    return m_towerData;
}
