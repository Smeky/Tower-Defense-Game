#ifndef TARGETTOWER_H
#define TARGETTOWER_H

#include "TowerFramework.h"
#include "IButton.h"
#include "ButtonIcon.h"
#include "TooltipManager.h"

class PlayState;

enum TOWER_ID {
    TOWER_PLASMA = 1,
    TOWER_PLASMA_MACHINE,
    TOWER_PLASMA_SNIPER,
    TOWER_BEAM,
    TOWER_SLOWER,
    TOWER_BOMBER,
};

class TargetTower {
public:
    void targetTower    ( Engine* game, TowerFramework* tower );
    void freeTarget     ();
    void handleEvents   ( Engine* game, PlayState* state, SDL_Event event, SDL_Point mousePosition );
    void update         ( Engine* game );
    void render         ( Engine* game );
    bool isSelected     () { return m_tower != NULL; }
    bool wasEvent       () { return m_wasEvent; }
private:
    void handleClick( Engine* game, int id );
    std::vector<ButtonIcon> m_buttons;
    TowerFramework* m_tower;
    TooltipManager  m_tooltipManager;
    int     m_buttonID;
    int     m_tpButtonID;
    bool    m_wasEvent;


};

#endif // TARGETTOWER_H
