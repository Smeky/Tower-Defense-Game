#include "hud/TooltipManager.h"
#include "hud/TooltipWarning.h"
#include "hud/TooltipDescription.h"

#include "iostream"
using namespace std;

void TooltipManager::createTooltipDescription( Engine* game, Tower_data data, int x, int y ) {
    m_description = new TooltipDescription( game, data, x, y );
}

void TooltipManager::createTooltipDescription( Engine* game, Enemy_data data, int x, int y ) {
    m_description = new TooltipDescription( game, data, x, y );
}

void TooltipManager::createTooltipWarning( Engine* game, std::string text, int x, int y, bool timed ) {
    setupTooltipWarning( game, text, x, y, TOOLTIP_NONE, timed );
}

void TooltipManager::createTooltipWarningLeft( Engine* game, std::string text, int x, int y, bool timed ) {
    setupTooltipWarning( game, text, x, y, TOOLTIP_LEFT, timed );
}

void TooltipManager::createTooltipWarningRight( Engine* game, std::string text, int x, int y, bool timed ) {
    setupTooltipWarning( game, text, x, y, TOOLTIP_RIGHT, timed );
}

void TooltipManager::createTooltipWarningUp( Engine* game, std::string text, int x, int y, bool timed ) {
    setupTooltipWarning( game, text, x, y, TOOLTIP_UP, timed );
}

void TooltipManager::createTooltipWarningDown( Engine* game, std::string text, int x, int y, bool timed ) {
    setupTooltipWarning( game, text, x, y, TOOLTIP_DOWN, timed );
}

void TooltipManager::close() {
    if( m_warning != NULL ) {
        delete m_warning;
        m_warning = NULL;
    }

    if( m_description != NULL ) {
        delete m_description;
        m_description = NULL;
    }
}

void TooltipManager::closeWarning() {
    if( m_warning != NULL ) {
        delete m_warning;
        m_warning = NULL;
    }
}

void TooltipManager::closeDescription() {
    if( m_description != NULL ) {
        delete m_description;
        m_description = NULL;
    }
}

void TooltipManager::update( Engine* game ) {
    if( m_warning != NULL ) {
        m_warning->update( game );

        if( m_displayFade ) {
            m_displayProgress += m_displayVelocity * game->getTimeDelta();

            if( m_displayProgress >= m_displayTime ) {
                m_warning->doFade();
            }

            if( m_warning->isFaded() ) {
                delete m_warning;
                m_warning = NULL;
            }
        }
    }
}

void TooltipManager::render( Engine* game ) {
    if( m_warning != NULL ) {
        m_warning->render( game );
    }

    if( m_description != NULL ) {
        m_description->render( game );
    }
}

void TooltipManager::setupTooltipWarning( Engine* game, std::string text, int x, int y, int side, bool timed ) {
    m_warning = new TooltipWarning( text, { x, y, game->getTextureW( text ) + 40, game->getTextureH( text ) + 15 }, side );

    m_displayProgress = 0;

    if( timed ) m_displayFade = true;
    else        m_displayFade = false;
}
