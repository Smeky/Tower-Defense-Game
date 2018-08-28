#ifndef IBUTTON_H
#define IBUTTON_H

#include "Engine.h"

class IButton {
public:
    virtual ~IButton() {}

    virtual void handleEvents( Engine* game, SDL_Event event, SDL_Point mousePosition );
    virtual void update( Engine* game, float timeStep );
    virtual void render( Engine* game ) {};

    SDL_Rect getBox     () { return m_box; }
    int getID           () { return m_id; }
    void setClicked     ( bool clicked ) { m_clicked = clicked; }
    void setSelect      ( bool select ) { m_selected = select; }
    void setXPosition   ( int x );
    void setYPosition   ( int y );
    bool isMouseover    () { return m_mouseover; }
    bool isClicked      () { return m_clicked; }
    bool isPressed      () { return m_pressed; }
    bool isSelected     () { return m_selected; }
protected:
    IButton( int x, int y, int w, int h, int id );
    IButton( int id );

    SDL_Rect m_box;

    int m_id;
    float m_alpha;
    int m_alphaVelocity;

    SDL_Keycode m_hotkey;

    bool m_clicked;
    bool m_pressed;
    bool m_mouseover;
    bool m_selected;
};

#endif // IBUTTON_H
