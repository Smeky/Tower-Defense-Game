#ifndef MENUOPTIONS_H
#define MENUOPTIONS_H

#include "IButton.h"
#include "OptionsPgVideo.h"
#include "OptionsPgAudio.h"

class MenuState;

class MenuOptions {
public:
    void init           ( Engine* game );
    void close          ();
    void handleEvents   ( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update         ( Engine* game, MenuState* state, float timeStep );
    void render         ( Engine* game );
private:
    void handleClick( Engine* game, MenuState* state, int id );
    std::vector<IButton*> m_pgButtons;
    OptionsPgVideo m_pgVideo;
    OptionsPgAudio m_pgAudio;
    SDL_Rect    m_bgBox;
    int         m_currPage;
};

#endif // MENUOPTIONS_H
