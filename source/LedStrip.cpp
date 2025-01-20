#include "LedStrip.hpp"
#include "Logger.hpp"

LedStrip::LedStrip()
{

}

LedStrip::LedStrip(const LedStripConfig &config, int virtualFirstLedNumber, Adafruit_NeoPXL8 *pixels)
    : config(config), virtualFirstLedNumber(virtualFirstLedNumber), pixels(pixels)
{
    Logger::log(LogLevel::DEBUG, "[LedStrip] virtualFirstLedNumber: %d", virtualFirstLedNumber);

    for(int i = 0; i < config.getNumLeds(); i++) {
        this->ledsColors.emplace_back(std::make_unique<Color>(0, 0, 0));
    }
}

void LedStrip::setLedColor(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue)
{
    if(ledNumber >= this->getLedsCount()) {
        Logger::log(LogLevel::WARNING, "[LedStrip] Invalid led number");
        return;
    }

    const uint8_t gamma8[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
        1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
        2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
        5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9,  10,
        10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
        17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
        25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
        37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
        51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
        69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
        90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
        115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
        144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
        177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
        215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
    };

    int fixedLedNumber = this->virtualFirstLedNumber + ledNumber;
    //Logger::log(LogLevel::DEBUG, "[LedStrip] setLedColor for strip: %d, and diode: %d (aka virtual diode: %d), and color: (%d %d %d)", static_cast<int>(this->getStripId()), ledNumber, fixedLedNumber, red, green, blue);

    // calculate brightness
    float brightnessRatio = this->brightness / 255.f;
    uint8_t fixedRed = static_cast<uint8_t>(red * brightnessRatio);
    uint8_t fixedGreen = static_cast<uint8_t>(green * brightnessRatio);
    uint8_t fixedBlue = static_cast<uint8_t>(blue * brightnessRatio);

    this->ledsColors[ledNumber]->setColor(red, green, blue);
    this->pixels->setPixelColor(fixedLedNumber, gamma8[fixedRed], gamma8[fixedGreen], gamma8[fixedBlue]);
}

Color* LedStrip::getLedColor(uint8_t ledNumber)
{
    return this->ledsColors[ledNumber].get();
}

void LedStrip::show()
{
    //Logger::log(LogLevel::DEBUG, "[LedStrip] show");
    this->pixels->show();
}

void LedStrip::setBrightness(uint8_t brightness)
{
    this->brightness = brightness;

    for(int i = 0; i < config.getNumLeds(); i++) {
        Color* color = this->ledsColors[i].get();
        this->setLedColor(i, color->getRed(), color->getGreen(), color->getBlue());
    }
}

int LedStrip::getLedsCount()
{
    return this->config.getNumLeds();
}

StripId LedStrip::getStripId()
{
    return this->config.getStripId();
}
