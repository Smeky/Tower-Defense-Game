#ifndef BUTTONTOWERSLOWER_H
#define BUTTONTOWERSLOWER_H

#include "IButton.h"

class ButtonTowerSlower : public IButton {
public:
    ButtonTowerSlower( int x, int y, int w, int h, int id );

    void update( Engine* game, float timeStep );
    void render( Engine* game );
private:
    SDL_Rect m_towerBox;
};

#endif // BUTTONTOWERSLOWER_H
