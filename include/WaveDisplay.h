#ifndef WAVEDISPLAY_H
#define WAVEDISPLAY_H

#include "string"
#include "IButton.h"

class WaveDisplay : public IButton {
public:
    WaveDisplay( Engine* game, Enemy_data data, int amount, SDL_Rect waveBox, int id, int y = 0 );
    void update( Engine* game, float timeStep );
    void render( Engine* game );

    void skipWave() { m_skip = true; }
    void waveSkiped() { m_skip = false; }

    Enemy_data getData() { return m_enemyData; }
    int getAmount() { return m_amount; }
    SDL_Rect* getBox() { return &m_box; }
    SDL_Rect* getTextureBox() { return &m_textureBox; }

    bool isDone() { return m_done; }
private:
    Enemy_data  m_enemyData;
    Texture     m_text;
    SDL_Rect    m_textureBox;
    SDL_Rect    m_waveBox;
    int         m_amount;
    int         m_moveVelocity;
    int         m_skipVelocity;
    float       m_position;
    bool        m_done;
    bool        m_skip;
    bool        m_textCreated;
};

#endif // WAVEDISPLAY_H
