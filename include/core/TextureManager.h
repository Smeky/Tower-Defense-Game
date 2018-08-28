#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H

#include "Texture.h"
#include "map"

class Engine;

class TextureManager {
public:
    bool loadMedia( Engine* game );
    void makeText( Engine* game, std::string name, std::string text, TTF_Font* font, SDL_Color color );
    void close();

    void setTextureAlpha( std::string name, Uint8 alpha );
    void drawTexture( std::string name, SDL_Renderer* renderer,
                      int x, int y,
                      SDL_Rect* clip = NULL, SDL_Rect* stretch = NULL,
                      bool centHor = false, bool centVer = false,
                      float angle = 0.0 );

    int getTextureW( std::string name ) { return m_textures[ name ].getWidth(); }
    int getTextureH( std::string name ) { return m_textures[ name ].getHeight(); }
private:
    std::map<std::string,Texture> m_textures;
};

#endif // TEXTURECONTAINER_H
