#include "core\Level.h"
#include "iostream"
#include "cstdlib"
#include "core\tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool Level::loadLevelFromFile( std::string path, Engine* game ) {
    bool success = true;

    XMLDocument file;

    if( file.LoadFile( path.c_str() ) != XML_NO_ERROR ) {
        cout << "Failed to load map from: " << path << endl;
        success = false;
    }
    else {
        XMLElement* mapElement = file.FirstChildElement( "map" );

        int mapTileWidth   = atoi( mapElement->Attribute( "width" ) );
        int mapTileHeight  = atoi( mapElement->Attribute( "height" ) );

        int tileWidth   = atoi( mapElement->Attribute( "tilewidth" ) );
        int tileHeight  = atoi( mapElement->Attribute( "tileheight" ) );

        m_pathWaves = mapElement->Attribute( "waves" );

        m_mapWidth  = mapTileWidth  * tileWidth;
        m_mapHeight = mapTileHeight * tileHeight;

        mapElement = mapElement->FirstChildElement( "tileset" );

        int tilesetTileWidth    = atoi( mapElement->Attribute( "tilewidth" ) );
        int tilesetTileHeight   = atoi( mapElement->Attribute( "tileheight" ) );

        mapElement = mapElement->FirstChildElement( "image" );

        int tilesetWidth   = atoi( mapElement->Attribute( "width" ) );
        int tilesetHeight  = atoi( mapElement->Attribute( "height" ) );

        // Setup tileset clips
        vector<SDL_Rect> tilesetClip;
        for( int i = 0; i < tilesetHeight / tilesetTileHeight; i++ ) {
            for( int j = 0; j < tilesetWidth / tilesetTileWidth; j++ ) {
                tilesetClip.push_back( { j * tilesetTileWidth,
                                         i * tilesetTileHeight,
                                         tilesetTileWidth,
                                         tilesetTileHeight } );
            }
        }

        mapElement = file.FirstChildElement( "map" )->FirstChildElement( "layer" );

        // Store map base
        vector<int> mapBaseTileData;
        for( XMLElement* tile = mapElement->FirstChildElement( "data" )->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement() ) {
            mapBaseTileData.push_back( atoi( tile->Attribute( "gid" ) ) );
        }

        // For every block in map setup tile and add dimension to grid
        for( int i = 0; i < mapTileHeight; i++ ) {
            for( int j = 0; j < mapTileWidth; j++ ) {
                int pos = i * mapTileWidth + j;

                m_tiles.push_back( Tile( tilesetClip[ mapBaseTileData[ pos ] - 1 ] ) );

                if( game->getWindowW() > game->getWindowBaseW() && j == 0 ) {
                    m_grid.push_back( { j * tileWidth - 1,
                                        i * tileHeight,
                                        tileWidth,
                                        tileHeight } );
                }
                else {
                    m_grid.push_back( { j * tileWidth,
                                        i * tileHeight,
                                        tileWidth,
                                        tileHeight } );
                }

            }
        }

        mapElement = mapElement->NextSiblingElement();

        // Store map objects layer #1
        vector<int> mapNeonTileData;
        for( XMLElement* tile = mapElement->FirstChildElement( "data" )->FirstChildElement(); tile != NULL; tile = tile->NextSiblingElement() ) {
            mapNeonTileData.push_back( atoi( tile->Attribute( "gid" ) ) );
        }

        // For every block in map setup tile and add dimension to grid
        for( int i = 0; i < mapTileHeight; i++ ) {
            for( int j = 0; j < mapTileWidth; j++ ) {
                int pos = i * mapTileWidth + j;

                m_neons.push_back( Tile( tilesetClip[ mapNeonTileData[ pos ] - 1 ] ) );
            }
        }

        // Store path waypoints -> used by enemies
        for( XMLElement* waypoint = file.FirstChildElement( "map" )->FirstChildElement( "objectgroup" )->FirstChildElement(); waypoint != NULL; waypoint = waypoint->NextSiblingElement() ) {
            m_pathGrid.push_back( { atoi( waypoint->Attribute( "x" ) ),
                                    atoi( waypoint->Attribute( "y" ) ) - tileHeight,
                                    tileWidth,
                                    tileHeight } );
        }

        if( game->getWindowBaseW() != game->getWindowW() ) {
            for( int i = 0; i < (int)m_pathGrid.size(); i++ ) {
                m_pathGrid[ i ].x = game->calcByResW( m_pathGrid[ i ].x );
                m_pathGrid[ i ].y = game->calcByResW( m_pathGrid[ i ].y );
                m_pathGrid[ i ].w = game->calcByResW( m_pathGrid[ i ].w );
                m_pathGrid[ i ].h = game->calcByResW( m_pathGrid[ i ].h );
            }

            for( int i = 0; i < (int)m_grid.size(); i++ ) {
                m_grid[ i ].x = game->calcByResW( m_grid[ i ].x );
                m_grid[ i ].y = game->calcByResW( m_grid[ i ].y );
                m_grid[ i ].w = game->calcByResW( m_grid[ i ].w ) + 1;
                m_grid[ i ].h = game->calcByResW( m_grid[ i ].h ) + 1;
            }

            m_mapWidth  = game->calcByResW( m_mapWidth );
            m_mapHeight = game->calcByResW( m_mapHeight );
        }
    }

    return success;
}

void Level::close() {
    m_grid.clear();
    m_pathGrid.clear();
    m_tiles.clear();

    m_mapWidth = 0;
    m_mapHeight = 0;
}

void Level::render( Engine* game ){
    // Render all base tiles
    for( int i = 0; i < (int)m_grid.size(); i++ ) {
        m_tiles[ i ].render( game, m_grid[ i ] );
    }

    // Render all neons
    for( int i = 0; i < (int)m_grid.size(); i++ ) {
        m_neons[ i ].render( game, m_grid[ i ] );
    }
}
