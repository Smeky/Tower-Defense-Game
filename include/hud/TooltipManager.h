#ifndef TOOLTIPMANAGER_H
#define TOOLTIPMANAGER_H

#include "core/Engine.h"

class TooltipWarning;
class TooltipDescription;

enum TOOLTIP_ARROW {
    TOOLTIP_NONE,
    TOOLTIP_LEFT,
    TOOLTIP_RIGHT,
    TOOLTIP_UP,
    TOOLTIP_DOWN
};

class TooltipManager {
public:
    void createTooltipDescription   ( Engine* game, Tower_data data, int x, int y );
    void createTooltipDescription   ( Engine* game, Enemy_data data, int x, int y );
    void createTooltipWarning       ( Engine* game, std::string text, int x, int y, bool timed = false );
    void createTooltipWarningLeft   ( Engine* game, std::string text, int x, int y, bool timed = false );
    void createTooltipWarningRight  ( Engine* game, std::string text, int x, int y, bool timed = false );
    void createTooltipWarningUp     ( Engine* game, std::string text, int x, int y, bool timed = false );
    void createTooltipWarningDown   ( Engine* game, std::string text, int x, int y, bool timed = false );
    void close();
    void closeWarning();
    void closeDescription();

    void update( Engine* game );
    void render( Engine* game );
private:
    void setupTooltipWarning( Engine* game, std::string text, int x, int y, int side, bool timed = false );

    TooltipWarning* m_warning;
    TooltipDescription* m_description;
    int     m_displayTime       = 40;
    int     m_displayVelocity   = 20;
    float   m_displayProgress;
    bool    m_displayFade;
};

#endif // TOOLTIPMANAGER_H
