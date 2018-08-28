#ifndef MENUUPGRADES_H
#define MENUUPGRADES_H

#include "IButton.h"

class MenuState;

class MenuUpgrades {
public:
    void init( Engine* game );
    void close();

    void handleEvents   ( Engine* game, MenuState* state, SDL_Event event, SDL_Point mousePosition );
    void update         ( Engine* game, MenuState* state, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick    ( Engine* game, MenuState* state, int id );

    std::vector<IButton*> m_topButtons;
    std::vector<IButton*> m_talButtons;
    std::vector<IButton*> m_upgButtons;
    SDL_Rect    m_backgroundBox;
    SDL_Rect    m_talPlasmaBox;
    SDL_Rect    m_talBeamBox;
    SDL_Rect    m_talSlowerBox;
    SDL_Rect    m_talBomberBox;
    int         m_page;
    int         m_ButEvent;
};

#endif // MENUUPGRADES_H
