#ifndef FIREEFFECT_H
#define FIREEFFECT_H

#include "Engine.h"

class FireEffect {
public:
    FireEffect( Engine* game, std::string texture, int x, int y, int w, int h );

    void update( Engine* game, float timeStep );
    void render( Engine* game );

    void enableAlpha    ( int velocity, float time );
    void disableAlpha   ();
    void setAlphaVel    ( int velocity );

    void setTimer   ( float time );
    void reset      ();
private:
    std::string m_texture;
    SDL_Rect    m_box;
    bool        m_alphaEnabled;
    int         m_alphaVelocity;
    Uint8       m_alpha;
    float       m_displayTime;
    float       m_timeProgress;
};

#endif // FIREEFFECT_H
