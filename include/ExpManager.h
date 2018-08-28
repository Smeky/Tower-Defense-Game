#ifndef EXPMANAGER_H
#define EXPMANAGER_H

#include "Engine.h"

class ExpManager  {
public:
    void init   ( Engine* game, SDL_Rect box );
    void update ( Engine* game, float timeStep );
    void render ( Engine* game );

    void addExp ( int amount );
private:
    Texture m_textCurXP;
    Texture m_textMaxXP;
    Texture m_textLevel;
    Texture m_textSlash;
    Texture m_textLvShort;
    SDL_Rect m_barBox;       // Background of experience bar
    SDL_Rect m_progBox;      // Proggress bar of experience
    int m_exp;      // Current player experience
    int m_plv;      // Player level
    int m_maxXp;    // Xp required to level up
};

#endif // EXPMANAGER_H
