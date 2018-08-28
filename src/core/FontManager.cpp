#include "core\FontManager.h"

#include "iostream"
using namespace std;

bool FontManager::loadFont() {
    m_calibriNormal     = TTF_OpenFont( "media/fonts/Calibri.ttf", 16 );
    m_calibriNormalBold = TTF_OpenFont( "media/fonts/Calibri.ttf", 16 );
    m_calibriLarge      = TTF_OpenFont( "media/fonts/Calibri.ttf", 24 );

    TTF_SetFontStyle( m_calibriNormalBold, TTF_STYLE_BOLD );

    m_fonts.insert( std::pair<std::string,TTF_Font*>( "FONT_CALIBRI_NORMAL",        m_calibriNormal ) );
    m_fonts.insert( std::pair<std::string,TTF_Font*>( "FONT_CALIBRI_LARGE" ,        m_calibriLarge  ) );
    m_fonts.insert( std::pair<std::string,TTF_Font*>( "FONT_CALIBRI_NORMAL_BOLD",   m_calibriNormalBold ) );
}

void FontManager::close() {
    TTF_CloseFont( m_calibriNormal );
    TTF_CloseFont( m_calibriNormalBold );
    TTF_CloseFont( m_calibriLarge  );
}
