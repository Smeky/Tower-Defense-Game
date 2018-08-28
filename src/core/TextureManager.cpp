#include "core\TextureManager.h"
#include "core\Engine.h"

#include "iostream"
using namespace std;

#include "core\tinyxml2.h"
using namespace tinyxml2;

bool TextureManager::loadMedia( Engine* game ) {
    bool success = true;

    XMLDocument file;

    if( file.LoadFile( "media/data/files.xml" ) != XML_NO_ERROR ) {
        cout << "Failed to load file at: media/data/files.xml" << endl;
        cout << "Perhaps there is a file missing" << endl;

        success = false;
    }
    else {
        XMLElement* element;

        element = file.FirstChildElement( "textures" );

        for( XMLElement* data = element->FirstChildElement(); data != NULL; data = data->NextSiblingElement() ) {
            m_textures.insert( { data->Attribute( "name" ), Texture() } );
            m_textures[ data->Attribute( "name" ) ].loadFromFile( data->Attribute( "path" ), game->getRenderer() );
        }

        element = file.FirstChildElement( "text" );

        for( XMLElement* data = element->FirstChildElement(); data != NULL; data = data->NextSiblingElement() ) {
            m_textures.insert( { data->Attribute( "name" ), Texture() } );
            m_textures[ data->Attribute( "name" ) ].loadFromText( data->Attribute( "text" ),
                                                                   game->getRenderer(),
                                                                   game->getFont( data->Attribute( "font" ) ), {
                                                                   (Uint8)data->IntAttribute( "r" ),
                                                                   (Uint8)data->IntAttribute( "g" ),
                                                                   (Uint8)data->IntAttribute( "b" ) } );
        }
    }

    return success;
}

void TextureManager::makeText( Engine* game, std::string name, std::string text, TTF_Font* font, SDL_Color color ) {
    std::map<std::string,Texture>::iterator it = m_textures.find( name );
    if( it != m_textures.end() ) {
        m_textures.erase( name );
        m_textures.insert( { name, Texture() } );
        m_textures[ name ].loadFromText( text, game->getRenderer(), font, color );
    }
    else {
        m_textures.insert( { name, Texture() } );
        m_textures[ name ].loadFromText( text, game->getRenderer(), font, color );
    }
}

void TextureManager::close() {
    m_textures.clear();
}

void TextureManager::setTextureAlpha( std::string name, Uint8 alpha ) {
    m_textures[ name ].setAlphamode( alpha );
}

void TextureManager::drawTexture( std::string name, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, SDL_Rect* stretch, bool centHor, bool centVer, float angle ) {
    m_textures[ name ].render( x, y, renderer, clip, stretch, centHor, centVer, angle );
}
