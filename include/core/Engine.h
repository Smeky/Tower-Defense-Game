#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#undef main

#include "string"
#include "vector"

#include "ResourceManager.h"
#include "TextureManager.h"
#include "SaveManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "core/Timer.h"

enum MENU_STATE {
    MENU_MAIN,
    MENU_PLAY,
    MENU_OPTIONS,
    MENU_ACHIEVS,
    MENU_CREDITS,
};

class IGameState;

class Engine {
public:
    bool init();
    void close();

    void handleEvents();
    void update();
    void render();
    void DrawRadius( float radius, int x, int y );

    void setWindowSize( int w, int h );

    void changeState( IGameState* state );
    void pushState( IGameState* state );
    void popState();

    void setNewLevel( Level_data* data ) { m_newLvData = data; }
    Level_data* getNewLevel() { return m_newLvData; }

    bool checkCollision( SDL_Rect a, SDL_Rect b );
    bool checkMouseover( SDL_Point pos, SDL_Rect* box );

    float calcDistance( float x1, float x2, float y1, float y2 );
    float calcAngle( float x1, float x2, float y1, float y2 );
    float calcDegreeToRadian( float degree );
    float calcRadianToDegree( float radian );
    float calcByResW( float w );
    float calcByResH( float h );
    void setRotationBetweenObjects( SDL_Rect* origin, SDL_Rect* target, SDL_Rect* rotator, float distance );

    SDL_Renderer* getRenderer() { return m_renderer; }

    float getTimeDelta() { return m_timeDelta; }

    TTF_Font* getFont( std::string name )  { return m_fontManager.getFont( name ); }

    void createText( std::string name, std::string text, TTF_Font* font, SDL_Color color );

    void playSound( std::string name ) { m_soundManager.playSound( name ); }
    void playMusic( std::string name ) { m_soundManager.playMusic( name ); }

    void setTextureAlpha( std::string name, Uint8 alpha );
    void drawTexture( std::string name, int x, int y, SDL_Rect* clip = NULL, SDL_Rect* stretch = NULL, bool centHor = false, bool centVer = false, float angle = 0.0 );

    std::string intToString( int number );

    ResourceManager Resources() { return m_resources; }
    SaveManager* Saves() { return &m_saveManager; }
    SoundManager* Sounds() { return &m_soundManager; }

    int getWindowW() { return m_windowW; }
    int getWindowH() { return m_windowH; }

    int getWindowBaseW() { return m_windowBaseW; }
    int getWindowBaseH() { return m_windowBaseH; }

    int getTextureW( std::string name ) { return m_textureManager.getTextureW( name ); }
    int getTextureH( std::string name ) { return m_textureManager.getTextureH( name ); }

    bool isRunning() { return m_running; }

    void setQuit() { m_running = false; }
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    TextureManager m_textureManager;
    FontManager m_fontManager;
    SoundManager m_soundManager;
    Timer m_timer;
    ResourceManager m_resources;
    SaveManager m_saveManager;

    Level_data* m_newLvData;

    std::vector<IGameState*> states;

    float m_timeDelta;

    int m_windowW;
    int m_windowH;

    static const int m_windowBaseW = 854;
    static const int m_windowBaseH = 480;

    bool m_running;
    bool m_newWindowSize;
};

#endif // ENGINE_H
