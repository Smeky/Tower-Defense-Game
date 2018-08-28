#ifndef BUTTONTOWERBEAM_H
#define BUTTONTOWERBEAM_H

#include "IButton.h"

class ButtonTowerBeam : public IButton {
public:
    ButtonTowerBeam( int x, int y, int w, int h, int id );

    void update( Engine* game, float timeStep );
    void render( Engine* game );
private:
    SDL_Rect m_towerBox;
};

#endif // BUTTONTOWERBEAM_H
