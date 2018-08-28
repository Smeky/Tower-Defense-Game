#ifndef TOOLTIPBUTTONTOWER_H
#define TOOLTIPBUTTONTOWER_H

#include "Engine.h"
#include "Texture.h"

class TooltipButtonTower {
public:
    TooltipButtonTower( int x, int y, Texture* name, Texture* stats, Texture* price, Texture* stat_range, Texture* stat_damage, Texture* stat_reload );

    void render( Engine* game );
private:
    SDL_Rect m_box;

    Texture* m_name;
    Texture* m_stats;
    Texture* m_price;
    Texture* m_statRange;
    Texture* m_statDamage;
    Texture* m_statReload;
};

#endif // TOOLTIPBUTTONTOWER_H
