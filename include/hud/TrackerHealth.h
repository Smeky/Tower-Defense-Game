#ifndef TRACKERHEALTH_H
#define TRACKERHEALTH_H

#include "core\Engine.h"

class TrackerHealth {
public:
    void init( Engine* game, int startHealth );

    void add( Engine* game, int amount );
    bool remove( Engine* game, int amount );
    void reset( Engine* game );

    void render( Engine* game, int x, int y );

    int getHealth() { return m_health; }
private:
    int m_health;
    int m_startHealth;

    Texture m_text;

    void update( Engine* game );
};

#endif // TRACKERHEALTH_H
