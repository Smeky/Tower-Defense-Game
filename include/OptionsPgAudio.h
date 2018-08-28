#ifndef OPTIONSPGAUDIO_H
#define OPTIONSPGAUDIO_H

#include "MenuPage.h"
#include "Slider.h"

class OptionsPgAudio : public MenuPage {
public:
    void init           ( Engine* game, SDL_Rect box );
    void close          ();
    void handleEvents   ( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update         ( Engine* game, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick    ( Engine* game, int id );
    void manageCheckboxes( Engine* game );
    std::vector<IButton*> m_checkboxes;
    std::vector<Slider*> m_sliders;
    std::vector<int> m_checkboxChange;
};

#endif // OPTIONSPGAUDIO_H
