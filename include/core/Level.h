#ifndef LEVEL_H
#define LEVEL_H

#include "SDL.h"
#undef main

#include "vector"
#include "string"

#include "Engine.h"
#include "Tile.h"

class Level {
public:
    bool loadLevelFromFile( std::string path, Engine* game );
    void close();
    void render( Engine* game );

    std::vector<SDL_Rect> &getPathgrid() { return m_pathGrid; }
    std::vector<SDL_Rect> &getGrid() { return m_grid; }

    std::string getWavePath() { return m_pathWaves; }

    int getMapWidth() { return m_mapWidth; }
    int getMapHeight() { return m_mapHeight; }
private:
    std::vector<SDL_Rect> m_grid;
    std::vector<SDL_Rect> m_pathGrid;
    std::vector<Tile> m_tiles;
    std::vector<Tile> m_neons;

    std::string m_pathWaves;

    int m_mapWidth;
    int m_mapHeight;
};

#endif // LEVEL_H
