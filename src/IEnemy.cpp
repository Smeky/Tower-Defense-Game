#include "IEnemy.h"

#include "iostream"
using namespace std;

IEnemy::IEnemy( Enemy_data data, SDL_Rect box, std::vector<SDL_Rect>& pathGrid ) {
    m_data      = data;
    m_box       = box;
    m_pathGrid  = pathGrid;

    m_movementVel   = data.speed;
    m_maximumHealth = data.health;
    m_currentHealth = data.health;

    m_xPosition = m_pathGrid[ 0 ].x + ( m_pathGrid[ 0 ].w - m_box.w ) / 2;
    m_yPosition = m_pathGrid[ 0 ].y + ( m_pathGrid[ 0 ].h - m_box.h ) / 2;

    m_prevPosition.x = m_box.x;
    m_prevPosition.y = m_box.y;

    m_maximumHealthBar.w = 25;
    m_maximumHealthBar.h = 4;

    m_currentHealthBar.w = m_maximumHealthBar.w;
    m_currentHealthBar.h = 4;

    m_wpCounter         = 0;
    m_distanceTraveled  = 0;

    m_dead      = false;
    m_finished  = false;
    m_slowed    = false;
    m_velFixed  = false;
}

void IEnemy::update( Engine* game, float timeStep ) {
    if( !m_velFixed ) {
        m_velFixed = true;

        m_movementVel = m_movementVel * ( (float)game->getWindowW() / game->getWindowBaseW() );
    }

    if( m_slowed ) {
        m_slowProgress += 10 * timeStep;

        if( m_slowProgress >= m_slowDutaion ) {
            m_slowed = false;
        }
    }
}

void IEnemy::move( float timeStep ) {
    int xCenteredWaypoint = m_pathGrid[ m_wpCounter ].x + ( m_pathGrid[ m_wpCounter ].w - m_box.w ) / 2;
    int yCenteredWaypoint = m_pathGrid[ m_wpCounter ].y + ( m_pathGrid[ m_wpCounter ].h - m_box.h ) / 2;

    int velocity;

    if( m_slowed ) {
        velocity = m_slowMovementVel;
    }
    else {
        velocity = m_movementVel;
    }

    m_distanceTraveled += timeStep * velocity;

    if( m_prevPosition.x < xCenteredWaypoint ) {
        m_xPosition += timeStep * velocity;

        if( m_xPosition >= xCenteredWaypoint ) {
            // If in corner, center position
            if( m_pathGrid[ m_wpCounter ].y != m_pathGrid[ m_wpCounter + 1 ].y ) {
                m_xPosition = xCenteredWaypoint;
            }

            m_prevPosition.x = xCenteredWaypoint;
            m_wpCounter++;
        }
    }
    else if( m_prevPosition.y < yCenteredWaypoint ) {
        m_yPosition += timeStep * velocity;

        if( m_yPosition >= yCenteredWaypoint ) {
            // If in corner, center position
            if( m_pathGrid[ m_wpCounter ].x != m_pathGrid[ m_wpCounter + 1 ].x ) {
                m_yPosition = yCenteredWaypoint;
            }

            m_prevPosition.y = yCenteredWaypoint;
            m_wpCounter++;
        }
    }
    else if( m_prevPosition.x > xCenteredWaypoint ) {
        m_xPosition -= timeStep * velocity;

        if( m_xPosition <= xCenteredWaypoint ) {
            // If in corner, center position
            if( m_pathGrid[ m_wpCounter ].y != m_pathGrid[ m_wpCounter + 1 ].y ) {
                m_xPosition = xCenteredWaypoint;
            }

            m_prevPosition.x = xCenteredWaypoint;
            m_wpCounter++;
        }
    }
    else if( m_prevPosition.y > yCenteredWaypoint ) {
        m_yPosition -= timeStep * velocity;

        if( m_yPosition <= yCenteredWaypoint ) {
            // If in corner, center position
            if( m_pathGrid[ m_wpCounter ].x != m_pathGrid[ m_wpCounter + 1 ].x ) {
                m_yPosition = yCenteredWaypoint;
            }

            m_prevPosition.y = yCenteredWaypoint;
            m_wpCounter++;
        }
    }

    if( m_wpCounter == (int)m_pathGrid.size() ) {
        m_finished = true;
    }

    m_box.x = (int)m_xPosition;
    m_box.y = (int)m_yPosition;

    m_maximumHealthBar.x = m_box.x + ( m_box.w - m_maximumHealthBar.w ) / 2;
    m_maximumHealthBar.y = m_box.y - 7;

    m_currentHealthBar.x = m_box.x + ( m_box.w - m_maximumHealthBar.w ) / 2;
    m_currentHealthBar.y = m_box.y - 7;
}


void IEnemy::dealDamage( float damage ) {
    m_currentHealth -= damage;

    if( m_currentHealth <= 0 ) {
        m_dead = true;
    }
}

void IEnemy::slow( float percentile, float duration ) {
    m_slowed = true;

    m_slowProgress  = 0.0;
    m_slowDutaion   = duration;

    m_slowMovementVel = ( (float)m_movementVel / 100 ) * ( 100 - percentile );
}

void IEnemy::render( Engine* game ) {
    game->drawTexture( m_data.tex, m_box.x, m_box.y, NULL, &m_box );
}

void IEnemy::renderHealth( Engine* game ) {
    if( m_currentHealth == m_maximumHealth ) {
        m_currentHealthBar.w = m_maximumHealthBar.w;
    }
    else {
        m_currentHealthBar.w = ( m_currentHealth / ( (float)m_maximumHealth / 100 ) ) * ( (float)m_maximumHealthBar.w / 100 );
    }

    if( m_currentHealthBar.w < 0 ) {
        m_currentHealthBar.w = 0;
    }

    SDL_SetRenderDrawColor( game->getRenderer(), 255, 0, 0, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_maximumHealthBar );

    SDL_SetRenderDrawColor( game->getRenderer(), 0, 255, 0, 255 );
    SDL_RenderFillRect( game->getRenderer(), &m_currentHealthBar );
}
