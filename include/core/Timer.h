#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"
#undef main

class Timer {
public:
    Timer();

    void start();   // Starts the timer
    void stop();    // Stops the timer

    void pause();
    void resume();

    Uint32 getTicks();

    bool isStarted() { return m_started; }
    bool isPaused() { return m_paused; }
private:
    Uint32 m_startTicks, m_pauseTicks;
    bool m_started, m_paused;
};

#endif // TIMER_H
