#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#undef main

#include "string"
#include "vector"

class Texture {
public:
    Texture();
    ~Texture();
    bool loadFromFile( std::string path, SDL_Renderer* renderer );
    bool loadFromText( std::string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color );
    bool lockTexture();
    bool unlockTexture();
    void free();
    void setBlendmode( SDL_BlendMode blending );
    void setAlphamode( Uint8 alpha );
    void setColormode( Uint8 R, Uint8 G, Uint8 B );
    void render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, SDL_Rect* stretch = NULL, bool centerVer = false, bool centerHor = false, double angle = 0.0 );
    Uint32 getPixel32( unsigned int x, unsigned int y );
    int getWidth();
    int getHeight();
private:
    SDL_Texture* m_texture;
    void *m_pixels;
    int m_pitch;
    int m_width, m_height;
};

#endif // TEXTURE_H
