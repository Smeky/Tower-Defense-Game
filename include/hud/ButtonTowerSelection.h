#ifndef BUTTONTOWERSELECTION_H
#define BUTTONTOWERSELECTION_H

#include "IButton.h"

class ButtonTowerSelection : public IButton {
public:
    ButtonTowerSelection( Tower_data data, SDL_Rect box, SDL_Keycode hotkey, int id );

    void update             ( Engine* game, float timeStep );
    void render             ( Engine* game );
    Tower_data getTowerData () { return m_towerData; }
private:
    Tower_data  m_towerData;
    SDL_Rect    m_towerBox;
};

#endif // BUTTONTOWERSELECTION_H
