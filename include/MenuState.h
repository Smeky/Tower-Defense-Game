#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "IGameState.h"
#include "core/Timer.h"

#include "hud/MenuMain.h"
#include "hud/MenuPlay.h"
#include "hud/MenuOptions.h"
#include "hud/TooltipManager.h"

class MenuState : public IGameState {
public:
    void init( Engine* game );
    void close();

    void handleEvents( Engine* game, SDL_Event event );
    void update( Engine* game );
    void render( Engine* game );

    void changeMenuState( int state_id );

    TooltipManager* getTpManager() { return &m_tpManager; }

    static MenuState* instance() { return &m_MenuState; }
private:
    static MenuState m_MenuState;

    int          m_menuState;
    Timer        m_timer;
    MenuMain     m_menuMain;
    MenuPlay     m_menuPlay;
    MenuOptions  m_menuOptions;
    TooltipManager m_tpManager;
};

#endif // MENUSTATE_H
