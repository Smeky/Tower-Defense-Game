#include "core\Texture.h"
#include "cstring"

#include "iostream"
using namespace std;

Texture::Texture() {
    m_texture = NULL;

    m_pixels = NULL;
    m_pitch  = 0;

    m_width  = 0;
    m_height = 0;
}

Texture::~Texture() {
    free();
}

bool Texture::loadFromFile( std::string path, SDL_Renderer* renderer ) {
    free();

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

    if( loadedSurface == NULL ) {
        cout << "IMG_Error: " << IMG_GetError() << endl;
    }
    else {
        SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL );

        if( formattedSurface == NULL ) {
            cout << "Unable to convert laoded surface to displat format!" << endl << "SDL_Error: " << SDL_GetError() << endl;
        }
        else {
            newTexture = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h );

            if( newTexture == NULL ) {
                cout << "Unable to create blank Texture!" << endl << "SDL_Error: " << SDL_GetError() << endl;
            }
            else {
                SDL_SetTextureBlendMode( newTexture, SDL_BLENDMODE_BLEND );

                SDL_LockTexture( newTexture, &formattedSurface->clip_rect, &m_pixels, &m_pitch );

                memcpy( m_pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h );

                m_width  = formattedSurface->w;
                m_height = formattedSurface->h;

                Uint32 *pixels = (Uint32*)m_pixels;
                int pixelCount = ( m_pitch / 4 ) * m_height;

                Uint32 colorKey    = SDL_MapRGB( formattedSurface->format, 255, 0, 255 );
                Uint32 transparent = SDL_MapRGBA( formattedSurface->format, 255, 0, 255, 0 );

                for( int i = 0; i < pixelCount; i++ ) {
                    if( pixels[ i ] == colorKey ) {
                        pixels[ i ] = transparent;
                    }
                }

                SDL_UnlockTexture( newTexture );
                m_pixels = NULL;
            }

            SDL_FreeSurface( formattedSurface );
        }

        SDL_FreeSurface( loadedSurface );
    }

    m_texture = newTexture;
    return m_texture != NULL;
}

bool Texture::loadFromText( std::string text, SDL_Renderer* renderer, TTF_Font* font, SDL_Color color ) {
    free();

    SDL_Surface* textSufrace = TTF_RenderText_Blended( font, text.c_str(), color );

    if( textSufrace == NULL ) {
        cout << "Unable to create text surface! TTF_Error: " << TTF_GetError() << endl;
    }
    else {
        m_texture = SDL_CreateTextureFromSurface( renderer, textSufrace );

        if( m_texture == NULL ) {
            cout << "Unable to create texture for rendered text! SDL_Error: %s" << SDL_GetError() << endl;
        }
        else {
            m_width  = textSufrace->w;
            m_height = textSufrace->h;
        }

        SDL_FreeSurface( textSufrace );
        textSufrace = NULL;
    }

    return m_texture != NULL;
}

bool Texture::lockTexture() {
    bool success = true;

    if( m_pixels != NULL ) {
        cout << "Texture is already locked!" << endl;
        success = false;
    }
    else {
        if( SDL_LockTexture( m_texture, NULL, &m_pixels, &m_pitch ) != 0 ) {
            cout << "Unable to lock texture!" << endl << "SDL_Error: " << SDL_GetError() << endl;
            success = false;
        }
    }

    return success;
}

bool Texture::unlockTexture() {
    bool success = true;

    if( m_pixels == NULL ) {
        cout << "Texture is not locked!" << endl;
        success = false;
    }
    else {
        m_pixels = NULL;
        m_pitch = 0;
    }

    return success;
}


void Texture::free() {
    if( m_texture != NULL ) {
        SDL_DestroyTexture( m_texture );
        m_texture = NULL;
        m_width   = 0;
        m_height  = 0;
    }
}

void Texture::setBlendmode( SDL_BlendMode blending ) {
    SDL_SetTextureBlendMode( m_texture, blending );
}

void Texture::setAlphamode( Uint8 alpha ) {
    SDL_SetTextureAlphaMod( m_texture, alpha );
}

void Texture::setColormode( Uint8 R, Uint8 G, Uint8 B ) {
    SDL_SetTextureColorMod( m_texture, R, G, B );
}

void Texture::render( int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* stretch, bool centerVer, bool centerHor, double angle ) {
    if( m_texture != NULL ) {
        SDL_Rect renderQuad = { x, y, m_width, m_height };

        if( clip != NULL ) {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        if( stretch != NULL ) {
            renderQuad.w = stretch->w;
            renderQuad.h = stretch->h;
        }

        if( centerVer ) {
            renderQuad.x = x - renderQuad.w / 2;
        }

        if( centerHor ) {
            renderQuad.y = y - renderQuad.h / 2;
        }

        SDL_RenderCopyEx( renderer, m_texture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE );
    }

}

Uint32 Texture::getPixel32( unsigned int x, unsigned int y ) {
    Uint32 *pixels = (Uint32*)m_pixels;
    return pixels[ ( y * ( m_pitch / 4 ) ) + x ];
}

int Texture::getWidth() {
    return m_width;
}

int Texture::getHeight() {
    return m_height;
}
