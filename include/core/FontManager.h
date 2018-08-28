#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "SDL_ttf.h"
#include "map"
#include "string"

class FontManager {
public:
    bool loadFont();
    void close();

    TTF_Font* getFont( std::string name ) { return m_fonts[ name ]; }
private:
    std::map<std::string,TTF_Font*> m_fonts;

    TTF_Font* m_calibriNormal;
    TTF_Font* m_calibriNormalBold;
    TTF_Font* m_calibriLarge;
};

#endif // FONTMANAGER_H
