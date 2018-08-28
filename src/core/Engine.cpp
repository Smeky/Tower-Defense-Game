#include "core/Engine.h"
#include "core/SDL2_gfxPrimitives.h"
#include "IGameState.h"
#include "sstream"
#include "math.h"

#include "iostream"
using namespace std;

bool Engine::init() {
    bool success = true;

    m_running       = false;
    m_newWindowSize = false;

    if( !m_saveManager.init() ) {
        cout << "Failed to initialize save file." << endl;
        return false;
    }

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
        cout << "SDL Initialization failed." << endl;
        success = false;
    }
    else {
        m_window = SDL_CreateWindow( "Smeky's TD",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    m_saveManager.getSaveData()->res_w, m_saveManager.getSaveData()->res_h,
                                    SDL_WINDOW_SHOWN );

        if( m_window == NULL ) {
            cout << "Failed to create the window." << endl;
            success = false;
        }
        else {
            m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

            if( m_renderer == NULL ) {
                cout << "Failed to create the renderer" << endl;
                success = false;
            }
            else {
                SDL_GetWindowSize( m_window, &m_windowW, &m_windowH );

                SDL_SetRenderDrawBlendMode( m_renderer, SDL_BLENDMODE_BLEND );
                SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );

                m_running = true;

                int imageFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imageFlags ) & imageFlags ) ) {
                    cout << "SDL_image initialization failed. Game sounds my not work." << endl;
                    success = false;
                }

                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
                    cout << "SDL_mixer initialization failed." << endl;
                }
                else Mix_Volume( -1, 32 );

                if( TTF_Init() < 0 ) {
                    cout << "SDL_ttf initialization failed. TTF_Error: " << TTF_GetError() << endl;
                    success = false;
                }

                m_fontManager.loadFont();

                if( !m_textureManager.loadMedia( this ) ) {
                    cout << "Failed to initialize textures." << endl;
                    success = false;
                }

                m_soundManager.loadMedia( this );

                if( !m_resources.init() ) {
                    cout << "Failed to initialize resources." << endl;
                    success = false;
                }

                m_timeDelta = 0;
                m_timer.start();
            }
        }
    }

    return success;
}

void Engine::close() {
    m_textureManager.close();
    m_fontManager.close();
    m_soundManager.close();

    SDL_DestroyRenderer( m_renderer );
    m_renderer = NULL;

    SDL_DestroyWindow( m_window );
    m_window = NULL;

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Engine::handleEvents() {
    SDL_Event event;

    while( SDL_PollEvent( &event ) != 0 ) {
        if( event.type == SDL_QUIT ) {
            m_running = false;
        }

        states.back()->handleEvents( this, event );
    }
}

void Engine::update() {
    m_timeDelta = m_timer.getTicks() / 1000.f;
    m_timer.start();

    states.back()->update(this);

    if( m_newWindowSize ) {
        m_newWindowSize = false;

        m_saveManager.getSaveData()->res_w = m_windowW;
        m_saveManager.getSaveData()->res_h = m_windowH;
        m_saveManager.saveSettings();

        SDL_SetWindowSize( m_window, m_windowW, m_windowH );
        SDL_SetWindowPosition( m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );

        states.back()->close();
        states.back()->init(this);
    }
}

void Engine::render() {
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    states.back()->render(this);

    SDL_RenderPresent( m_renderer );
}

void Engine::DrawRadius( float radius, int x, int y ) {
    circleRGBA(       m_renderer, x, y, radius    , 80, 130, 155, 180 );
    filledCircleRGBA( m_renderer, x, y, radius - 5, 130, 210, 255, 80 );
}

void Engine::setWindowSize( int w, int h ) {
    m_newWindowSize = true;

    m_windowW = w;
    m_windowH = h;
}

void Engine::changeState( IGameState* state ) {
    while( !states.empty() ) {
        states.back()->close();
        states.pop_back();
    }

    states.push_back( state );
    states.back()->init(this);
}

void Engine::pushState( IGameState* state ) {
    if( !states.empty() ) {
        states.back()->pause();
    }

    states.push_back( state );
    states.back()->init(this);
}

void Engine::popState() {
    if( !states.empty() ) {
        states.back()->close();
        states.pop_back();
    }

    if( !states.empty() ) {
        states.back()->resume();
    }
}

bool Engine::checkCollision( SDL_Rect a, SDL_Rect b ) {
    if( a.x > b.x + b.w ) {
        return false;
    }
    else if( a.x + a.w < b.x ) {
        return false;
    }
    else if( a.y > b.y + b.h ) {
        return false;
    }
    else if( a.y + a.h < b.y ) {
        return false;
    }

    return true;
}

bool Engine::checkMouseover( SDL_Point pos, SDL_Rect* box ) {
    if( pos.x > box->x && pos.x < box->x + box->w &&
        pos.y > box->y && pos.y < box->y + box->h ) {

        return true;
    }

    return false;
}

float Engine::calcDistance( float x1, float x2, float y1, float y2 ) {
    return sqrt( pow( x2 - x1, 2 ) + pow( y2 - y1, 2 ) );
}

float Engine::calcAngle( float x1, float x2, float y1, float y2 ) {
    return atan2( y2 - y1, x2 - x1 );
}

float Engine::calcDegreeToRadian( float degree ) {
    return degree * ( M_PI / 180.0 );
}

float Engine::calcRadianToDegree( float radian ) {
    return radian * 180.0 / M_PI;
}

float Engine::calcByResW( float w ) {
    return m_windowW * ( w / m_windowBaseW );
}

float Engine::calcByResH( float h ) {
    return m_windowH * ( h / m_windowBaseH );
}

void Engine::setRotationBetweenObjects( SDL_Rect* origin, SDL_Rect* target, SDL_Rect* rotator, float distance ) {
    float ox = origin->x + origin->w / 2;   // x of origin center
    float oy = origin->y + origin->h / 2;   // y of origin center

    float tx = target->x + target->w / 2;   // x of target center
    float ty = target->y + target->h / 2;   // y of target center

    double angle = calcAngle( ox, tx, oy, ty );

    float rx = rotator->x + rotator->w / 2;
    float ry = rotator->y + rotator->h / 2;

    float newx = ox + ( rx - ox ) * cos( angle ) - ( ry - oy ) * sin( angle );
    float newy = oy + ( rx - ox ) * sin( angle ) + ( ry - oy ) * cos( angle );

    rotator->x = (int)newx - rotator->w / 2;
    rotator->y = (int)newy - rotator->h / 2;
}

void Engine::createText( std::string name, std::string text, TTF_Font* font, SDL_Color color ) {
    m_textureManager.makeText( this, name, text, font, color );
}

string Engine::intToString( int number ) {
    ostringstream oss;

    oss << number;

    return oss.str();
}

void Engine::setTextureAlpha( std::string name, Uint8 alpha ) {
    m_textureManager.setTextureAlpha( name, alpha );
}

void Engine::drawTexture( std::string name, int x, int y, SDL_Rect* clip, SDL_Rect* stretch, bool centHor, bool centVer, float angle ) {
    m_textureManager.drawTexture( name, m_renderer, x, y, clip, stretch, centHor, centVer, angle );
}
