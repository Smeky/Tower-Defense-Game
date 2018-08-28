#ifndef SLIDER_H
#define SLIDER_H

#include "SliderButton.h"

class Slider : IButton {
public:
    Slider( int x, int y, int w, float minValue, float maxValue, float curValue );
    ~Slider();
    void handleEvents   ( Engine* game, SDL_Event event, SDL_Point mousePos );
    void update         ( Engine* game, float timeStep );
    void render         ( Engine* game );

    SliderButton* getButton() { return m_button; }
    float getMinValue() { return m_minValue; }
    float getMaxValue() { return m_maxValue; }
    float getCurrentValue() { return m_currentValue; }
    float getCurrentValueInPercent();
private:
    float calcPercentCurrentValue();

    SliderButton* m_button;
    float m_minValue;
    float m_maxValue;
    float m_currentValue;
};

#endif // SLIDER_H
