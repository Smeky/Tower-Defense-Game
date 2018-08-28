#ifndef BUTTONUPGS_H
#define BUTTONUPGS_H

#include "IButton.h"

class ButtonUpgs : public IButton {
public:
    ButtonUpgs( std::string text_adrs, int x, int y, int w, int h, int id );
    void update( Engine* game );
    void render( Engine* game );
private:
    std::string m_textAdrs;
};

#endif // BUTTONUPGS_H
