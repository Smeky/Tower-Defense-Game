#include "hud/MenuUpgrades.h"
#include "hud/ButtonMenu.h"
#include "hud/ButtonUpgs.h"
#include "ButtonIcon.h"
#include "MenuState.h"

#include "iostream"
using namespace std;

typedef std::vector<IButton*> _button;

enum BUTTON_ID {
    BUTTON_ID_TALENTS,
    BUTTON_ID_UPGRADES,
    BUTTON_ID_MENU,
    BUTTON_ID_TALENT_PLASMA_1,
    BUTTON_ID_TALENT_PLASMA_2,
    BUTTON_ID_TALENT_PLASMA_3,
    BUTTON_ID_TALENT_PLASMA_4,
    BUTTON_ID_TALENT_PLASMA_5,
    BUTTON_ID_TALENT_PLASMA_6,
    BUTTON_ID_TALENT_BEAM_1,
    BUTTON_ID_TALENT_BEAM_2,
    BUTTON_ID_TALENT_BEAM_3,
    BUTTON_ID_TALENT_BEAM_4,
    BUTTON_ID_TALENT_BEAM_5,
    BUTTON_ID_TALENT_BEAM_6,
    BUTTON_ID_TALENT_SLOWER_1,
    BUTTON_ID_TALENT_SLOWER_2,
    BUTTON_ID_TALENT_SLOWER_3,
    BUTTON_ID_TALENT_SLOWER_4,
    BUTTON_ID_TALENT_SLOWER_5,
    BUTTON_ID_TALENT_SLOWER_6,
    BUTTON_ID_TALENT_BOMBER_1,
    BUTTON_ID_TALENT_BOMBER_2,
    BUTTON_ID_TALENT_BOMBER_3,
    BUTTON_ID_TALENT_BOMBER_4,
    BUTTON_ID_TALENT_BOMBER_5,
    BUTTON_ID_TALENT_BOMBER_6,
};

enum UPGS_PAGE {
    PAGE_TALENTS,
    PAGE_UPGRADES,
};

void MenuUpgrades::init( Engine* game ) {
    m_backgroundBox.w = 720;
    m_backgroundBox.h = 450;
    m_backgroundBox.x = ( game->getWindowW() - m_backgroundBox.w ) / 2;
    m_backgroundBox.y = ( game->getWindowH() - m_backgroundBox.h ) / 2;

    m_talPlasmaBox.x = m_backgroundBox.x;
    m_talPlasmaBox.y = m_backgroundBox.y + 50;
    m_talPlasmaBox.w = 180;
    m_talPlasmaBox.h = m_backgroundBox.h - 50;

    m_talBeamBox.x = m_talPlasmaBox.x + m_talPlasmaBox.w;
    m_talBeamBox.y = m_backgroundBox.y + 50;
    m_talBeamBox.w = 180;
    m_talBeamBox.h = m_backgroundBox.h - 50;

    m_talSlowerBox.x = m_talBeamBox.x + m_talBeamBox.w;
    m_talSlowerBox.y = m_backgroundBox.y + 50;
    m_talSlowerBox.w = 180;
    m_talSlowerBox.h = m_backgroundBox.h - 50;

    m_talBomberBox.x = m_talSlowerBox.x + m_talSlowerBox.w;
    m_talBomberBox.y = m_backgroundBox.y + 50;
    m_talBomberBox.w = 180;
    m_talBomberBox.h = m_backgroundBox.h - 50;

    m_topButtons.push_back( new ButtonUpgs( "BUTTON_UPGS_MENU",        m_backgroundBox.x,       m_backgroundBox.y, 240, 50, BUTTON_ID_MENU ) );
    m_topButtons.push_back( new ButtonUpgs( "BUTTON_UPGS_TALENTS",     m_backgroundBox.x + 240, m_backgroundBox.y, 240, 50, BUTTON_ID_TALENTS ) );
    m_topButtons.push_back( new ButtonUpgs( "BUTTON_UPGS_UPGRADES",    m_backgroundBox.x + 480, m_backgroundBox.y, 240, 50, BUTTON_ID_UPGRADES ) );

    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2,      m_talPlasmaBox.y + 50,  45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_1 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2 - 40, m_talPlasmaBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_2 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2 + 40, m_talPlasmaBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_3 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2 - 40, m_talPlasmaBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_4 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2 + 40, m_talPlasmaBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_5 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talPlasmaBox.x + m_talPlasmaBox.w / 2,      m_talPlasmaBox.y + 350, 45, 45 }, 0, BUTTON_ID_TALENT_PLASMA_6 ) );

    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2,      m_talBeamBox.y + 50,  45, 45 }, 0, BUTTON_ID_TALENT_BEAM_1 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2 - 40, m_talBeamBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_BEAM_2 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2 + 40, m_talBeamBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_BEAM_3 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2 - 40, m_talBeamBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_BEAM_4 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2 + 40, m_talBeamBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_BEAM_5 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBeamBox.x + m_talBeamBox.w / 2,      m_talBeamBox.y + 350, 45, 45 }, 0, BUTTON_ID_TALENT_BEAM_6 ) );

    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2,      m_talSlowerBox.y + 50,  45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_1 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2 - 40, m_talSlowerBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_2 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2 + 40, m_talSlowerBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_3 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2 - 40, m_talSlowerBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_4 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2 + 40, m_talSlowerBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_5 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talSlowerBox.x + m_talSlowerBox.w / 2,      m_talSlowerBox.y + 350, 45, 45 }, 0, BUTTON_ID_TALENT_SLOWER_6 ) );

    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2,      m_talBomberBox.y + 50,  45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_1 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2 - 40, m_talBomberBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_2 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2 + 40, m_talBomberBox.y + 150, 45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_3 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2 - 40, m_talBomberBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_4 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2 + 40, m_talBomberBox.y + 250, 45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_5 ) );
    m_talButtons.push_back( new ButtonIcon( "NO_TEXTURE", { m_talBomberBox.x + m_talBomberBox.w / 2,      m_talBomberBox.y + 350, 45, 45 }, 0, BUTTON_ID_TALENT_BOMBER_6) );

    m_page = PAGE_TALENTS;
}

void MenuUpgrades::close() {
    while( !m_topButtons.empty() ) delete m_topButtons.back(), m_topButtons.pop_back();
    while( !m_talButtons.empty() ) delete m_talButtons.back(), m_talButtons.pop_back();
    while( !m_upgButtons.empty() ) delete m_upgButtons.back(), m_upgButtons.pop_back();
}

void MenuUpgrades::handleEvents( Engine* game, MenuState* state, SDL_Event event, SDL_Point mousePosition ) {
    for( _button::iterator it = m_topButtons.begin(); it != m_topButtons.end(); it++ ) {
        (*it)->handleEvents( game, event, mousePosition );
    }

    if( m_page == PAGE_TALENTS ) {
        for( _button::iterator it = m_talButtons.begin(); it != m_talButtons.end(); it++ ) {
            (*it)->handleEvents( game, event, mousePosition );

            if( (*it)->isClicked() ) {
                handleClick( game, state, (*it)->getID() );
            }
        }
    }
    else if( m_page == PAGE_UPGRADES ) {
        for( _button::iterator it = m_upgButtons.begin(); it != m_upgButtons.end(); it++ ) {
            (*it)->handleEvents( game, event, mousePosition );

            if( (*it)->isClicked() ) {
                handleClick( game, state, (*it)->getID() );
            }
        }
    }
}

void MenuUpgrades::update( Engine* game, MenuState* state, float timeStep ) {
    for( _button::iterator it = m_topButtons.begin(); it != m_topButtons.end(); it++ ) {
        (*it)->update( game, timeStep );

        if( (*it)->isClicked() ) {
            (*it)->setClicked( false );
            handleClick( game, state, (*it)->getID() );
        }
    }

    if( m_page == PAGE_TALENTS ) {
        for( _button::iterator it = m_talButtons.begin(); it != m_talButtons.end(); it++ ) {
            (*it)->update( game, timeStep );
        }
    }
    else if( m_page == PAGE_UPGRADES ) {
        for( _button::iterator it = m_upgButtons.begin(); it != m_upgButtons.end(); it++ ) {
            (*it)->update( game, timeStep );
        }
    }
}

void MenuUpgrades::render( Engine* game ) {
    SDL_SetRenderDrawColor( game->getRenderer(), 25, 50, 90, 255 );
    SDL_RenderClear( game->getRenderer() );

    SDL_SetRenderDrawColor( game->getRenderer(), 10, 20, 25, 200 );
    SDL_RenderFillRect( game->getRenderer(), &m_backgroundBox );

    for( _button::iterator it = m_topButtons.begin(); it != m_topButtons.end(); it++ ) {
        if( (*it)->getID() == m_page ) {
            (*it)->setClicked( true );
            (*it)->render( game );
            (*it)->setClicked( false );
        }
        else {
            (*it)->render( game );
        }
    }

    if( m_page == PAGE_TALENTS ) {
        SDL_SetRenderDrawColor( game->getRenderer(), 120, 120, 120, 120 );
        SDL_RenderDrawLine( game->getRenderer(), m_talBeamBox.x, m_talBeamBox.y + 20, m_talBeamBox.x, m_talBeamBox.y + m_talBeamBox.h - 20 );
        SDL_RenderDrawLine( game->getRenderer(), m_talSlowerBox.x, m_talSlowerBox.y + 20, m_talSlowerBox.x, m_talSlowerBox.y + m_talSlowerBox.h - 20 );
        SDL_RenderDrawLine( game->getRenderer(), m_talBomberBox.x, m_talBomberBox.y + 20, m_talBomberBox.x, m_talBomberBox.y + m_talBomberBox.h - 20 );

        for( _button::iterator it = m_talButtons.begin(); it != m_talButtons.end(); it++ ) {
            (*it)->render( game );
        }
    }
    else if( m_page == PAGE_UPGRADES ) {
        for( _button::iterator it = m_upgButtons.begin(); it != m_upgButtons.end(); it++ ) {
            (*it)->render( game );
        }
    }
}

void MenuUpgrades::handleClick( Engine* game, MenuState* state, int id ) {
    switch( id ) {
    // case BUTTON_ID_MENU:     state->changeMenuState( MENU_LEVELS ); break;
    case BUTTON_ID_TALENTS:  m_page = PAGE_TALENTS; break;
    case BUTTON_ID_UPGRADES: m_page = PAGE_UPGRADES; break;
    default:
//        state->getTpManager()->createTooltipWarning( game, "TEXT_TOOLTIP_NOT_READY_FUNCTION", 5, 5, true );
//        game->playSound( "SOUND_UI_ERROR" );

        break;
    }

}
