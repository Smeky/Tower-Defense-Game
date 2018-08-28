#ifndef OPTIONSPGVIDEO_H
#define OPTIONSPGVIDEO_H

#include "MenuPage.h"

class OptionsPgVideo : public MenuPage {
public:
    void init           ( Engine* game, SDL_Rect box );
    void update         ( Engine* game, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick    ( Engine* game, int id );
    SDL_Rect m_textResBox;
};

#endif // OPTIONSPGVIDEO_H
