#ifndef SOLID_COLOR_ANIMATION_HPP
#define SOLID_COLOR_ANIMATION_HPP

#include "LedStrip.hpp"
#include "Animation.hpp"
#include "AnimationManager.hpp"
#include "Color.hpp"

#include <algorithm>
#include <functional>

class SolidColorAnimation : public Animation {
    public:
    
    SolidColorAnimation(LedStrip* ledStrip, uint8_t red, uint8_t green, uint8_t blue, uint8_t speed);
    SolidColorAnimation(LedStrip* ledStrip, Color targetColor, uint8_t speed);
    
    void nextFrame();
    bool isFinished();

    private:
    Color generateNewFrameColor(Color currentColor);

    LedStrip* ledStrip;

    bool finished = false;
    Color targetColor;
    int speed;
};

#endif // SOLID_COLOR_ANIMATION_HPP