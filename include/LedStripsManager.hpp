#ifndef LED_STRIPS_MANAGER_HPP
#define LED_STRIPS_MANAGER_HPP

#include <memory>
#include <array>

#include "LedStrip.hpp"
#include "AnimationManager.hpp"
#include "StripId.hpp"

#include <Adafruit_NeoPXL8.h>

class LedStripsManager {
    public:
    //LedStripsManager();
    LedStripsManager(const std::vector<LedStripConfig>& configs);
    LedStrip* getStrip(StripId id);
    void setStripLedColor(StripId id, int diodeNumber, uint8_t red, uint8_t green, uint8_t blue);
    void setStripBrightness(StripId id, uint8_t brightness);
    void show(StripId id);
    Adafruit_NeoPXL8* getGlobalStrip();

    private:
    void calculateVirtualLeds(const std::vector<LedStripConfig>& configs);
    int getFirstStripLedNumber(StripId id, const std::vector<LedStripConfig>& configs);

    int totalVirtualLeds;
    int virtualLedsEachStrip;

    std::array<std::unique_ptr<LedStrip>, static_cast<int>(StripId::STRIP_MAX)> strips; 
    std::unique_ptr<Adafruit_NeoPXL8> pixels;
};

#endif // LED_STRIPS_MANAGER_HPP