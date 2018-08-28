#include "core\Tile.h"

Tile::Tile( SDL_Rect tilesetTypeClip ) {
    m_tilesetClip = tilesetTypeClip;
}

void Tile::render( Engine* game, SDL_Rect& box ) {
    if( m_tilesetClip.x >= 0 && m_tilesetClip.y >= 0 )
    game->drawTexture( "TILESET", box.x, box.y, &m_tilesetClip, &box );
}
