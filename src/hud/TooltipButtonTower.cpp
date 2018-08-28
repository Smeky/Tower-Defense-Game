#include "hud\TooltipButtonTower.h"

TooltipButtonTower::TooltipButtonTower( int x, int y, Texture* name, Texture* stats, Texture* price, Texture* stat_range, Texture* stat_damage, Texture* stat_reload ) {
    m_box.x = x;
    m_box.y = y;
    m_box.w = 150;
    m_box.h = 300;

    m_name = name;
    m_stats = stats;
    m_price = price;
    m_statRange = stat_range;
    m_statDamage = stat_damage;
    m_statReload = stat_reload;
}

void TooltipButtonTower::render( Engine* game ) {

}
