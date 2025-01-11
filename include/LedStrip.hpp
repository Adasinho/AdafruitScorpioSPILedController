#ifndef LEDSTRIP_HPP
#define LEDSTRIP_HPP

#include <cstdint>
#include <vector>
#include <memory>

#include "Color.hpp"
#include "LedStripConfig.hpp"

#include "pico/stdlib.h"

#include "Adafruit_NeoPXL8.h"

class LedStrip {
public:
    LedStrip();
    LedStrip(const LedStripConfig& config, int virtualFirstLedNumber, Adafruit_NeoPXL8* pixels);
    void setLedColor(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
    Color* getLedColor(uint8_t ledNumber);
    void show();
    void animate(uint8_t animationId);
    void setBrightness(uint8_t brightness);

    int getLedsCount();
    StripId getStripId();

private:
    LedStripConfig config;
    int virtualFirstLedNumber;
    Adafruit_NeoPXL8* pixels;
    std::vector<std::unique_ptr<Color>> ledsColors;
    uint8_t brightness = 255;
    // ... (ewentualne dodatkowe dane, np. stan animacji)
};

#endif // LEDSTRIP_HPP