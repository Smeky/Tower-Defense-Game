#ifndef BUTTONTOWERPLASMA_H
#define BUTTONTOWERPLASMA_H

#include "IButton.h"

class ButtonTowerPlasma : public IButton {
public:
    ButtonTowerPlasma( int x, int y, int w, int h, int id );

    void update( Engine* game, float timeStep );
    void render( Engine* game );
private:
    SDL_Rect m_towerBox;
};

#endif // BUTTONTOWERPLASMA_H
