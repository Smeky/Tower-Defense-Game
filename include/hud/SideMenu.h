#ifndef SIDEMENU_H
#define SIDEMENU_H

#include "IButton.h"
#include "ButtonTowerSelection.h"
#include "TooltipManager.h"

class PlayState;

class SideMenu {
public:
    void init               ( Engine* game, int gridWidth, int gridHeight );
    void close();
    void handleEvents       ( Engine* game, SDL_Event event, SDL_Point mousePosition );
    void update             ( Engine* game, PlayState* state, float timeStep );
    void render             ( Engine* game );
    SDL_Rect getMoneyBox    () { return m_moneyBox; }
    SDL_Rect getHealthBox   () { return m_healthBox; }
    SDL_Rect getWaveBox     () { return m_waveBox; }
    Tower_data getTowerData ();
    int getClickedTower     () { return m_selectedTower; }
    void resetClickedTower  () { m_selectedTower = 0; }
private:
    void handleClick( Engine* game, PlayState* state, int id );
    std::vector<IButton*> m_buttons;
    std::vector<ButtonTowerSelection*> m_towSlctBut;
    TooltipManager m_tpManager;
    Tower_data  m_towerData;
    SDL_Point   m_mousePos;
    SDL_Rect    m_botBox;
    SDL_Rect    m_sideBox;
    SDL_Rect    m_waveBox;
    SDL_Rect    m_moneyBox;
    SDL_Rect    m_healthBox;
    SDL_Rect    m_towerPlasmaIconBox;
    SDL_Rect    m_towerPlasmaNameBox;
    int         m_selectedTower;
    int         m_tpButtonID;
    bool        m_sellTower;
};

#endif // SIDEMENU_H
