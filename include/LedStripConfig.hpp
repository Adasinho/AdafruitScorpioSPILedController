#ifndef LED_STRIP_CONFIG_HPP
#define LED_STRIP_CONFIG_HPP

#include "StripId.hpp"

class LedStripConfig {
public:
    LedStripConfig() {}
    LedStripConfig(StripId id, int numLeds, int pinData) 
        : id(id), numLeds(numLeds), pinData(pinData) {}

    int getNumLeds() const { return numLeds; }
    int getPinData() const { return pinData; }
    StripId getStripId() const { return id; }

private:
    StripId id;
    int numLeds;   // Liczba diod LED na pasku
    int pinData;  // Numer pinu danych
};

#endif // LED_STRIP_CONFIG_HPP