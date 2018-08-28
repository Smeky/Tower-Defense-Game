#ifndef TOOLTIPDESCRIPTION_H
#define TOOLTIPDESCRIPTION_H

#include "TooltipManager.h"

class TooltipDescription {
public:
    TooltipDescription( Engine* game, Tower_data data, int x, int y );
    TooltipDescription( Engine* game, Enemy_data data, int x, int y );
    void render( Engine* game );
private:
    Tp_tower_stats  m_towerStats;
    Tp_enemy_stats  m_enemyStats;
    Tower_data  m_towerData;
    Enemy_data  m_enemyData;
    std::string m_towerDmgAdrs;
    std::string m_towerRngAdrs;
    std::string m_towerAtsAdrs;
    std::string m_towerPrcAdrs;
    std::string m_enemyHpsAdrs;
    std::string m_enemyWthAdrs;
    std::string m_enemySpdAdrs;
    SDL_Rect    m_box;
    int         m_type;
};

#endif // TOOLTIPDESCRIPTION_H
