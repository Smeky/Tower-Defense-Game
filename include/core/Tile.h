#ifndef TILE_H
#define TILE_H

#include "SDL.h"
#undef main

#include "Engine.h"

class Tile {
public:
    Tile( SDL_Rect tilesetTypeClip );
    void render( Engine* game, SDL_Rect& box );
private:
    SDL_Rect m_tilesetClip;
};

#endif // TILE_H
