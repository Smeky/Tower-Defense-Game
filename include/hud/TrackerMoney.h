#ifndef TRACKERMONEY_H
#define TRACKERMONEY_H

#include "core\Engine.h"

class TrackerMoney {
public:
    void init( Engine* game, int startMoney );

    void add( Engine* game, int amount );
    bool remove( Engine* game, int amount );
    void reset( Engine* game );

    void render( Engine* game, int x, int y );

    int getMoney() { return m_money; }
private:
    int m_money;
    int m_startMoney;

    Texture m_text;

    bool m_maxTextSet;

    void update( Engine* game );
};

#endif // TRACKERMONEY_H
