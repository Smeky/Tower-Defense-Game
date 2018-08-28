#ifndef MENUPLAY_H
#define MENUPLAY_H

#include "IButton.h"
#include "TooltipManager.h"
#include "TalentManager.h"
#include "LevelManager.h"
#include "ExpManager.h"

class MenuState;

class MenuPlay {
public:
    void init           ( Engine* game );
    void close          ();
    void handleEvents   ( Engine* game, MenuState* menu, SDL_Event event, SDL_Point mousePos );
    void update         ( Engine* game, MenuState* menu, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick    ( Engine* game, MenuState* menu, int id );
    std::vector<IButton*> m_pgButtons;  // Page buttons ( on the side of menu )
    std::string     m_levelPath;        // Address to selected level
    TooltipManager  m_tpManager;        // Manager of tooltips
    LevelManager    m_lvManager;        // Manager of level page
    TalentManager   m_tlManager;        // Manager of talent page
    ExpManager      m_xpManager;
    SDL_Rect        m_bgBox;            // Box of background
    int             m_currPage;         // Current menu page
};

#endif // MENUPLAY_H
