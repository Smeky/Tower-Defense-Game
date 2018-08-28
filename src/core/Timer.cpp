#include "core\Timer.h"
Timer::Timer() {
    m_started   = false;
    m_paused    = false;

    m_startTicks = 0;
    m_pauseTicks = 0;
}

void Timer::start() {
    m_started   = true;
    m_paused    = false;

    m_startTicks = SDL_GetTicks();
    m_pauseTicks = 0;
}

void Timer::stop() {
    if( m_started ) {
        m_started   = false;
        m_paused    = false;

        m_startTicks = 0;
        m_pauseTicks = 0;
    }
}

void Timer::pause() {
    if( m_started && !m_paused ) {
        m_paused = true;

        m_pauseTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;
    }
}

void Timer::resume() {
    if( m_started && m_paused ) {
        m_paused = false;

        m_startTicks = SDL_GetTicks() - m_pauseTicks;
        m_pauseTicks = 0;
    }
}

Uint32 Timer::getTicks() {
    Uint32 time = 0;

    if( m_started ) {
        if( m_paused ) {
            time = m_pauseTicks;
        }
        else {
            time = SDL_GetTicks() - m_startTicks;
        }
    }

    return time;
}
