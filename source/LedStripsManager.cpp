#include "LedStripsManager.hpp"

// LedStripsManager::LedStripsManager()
// {
    
// }

LedStripsManager::LedStripsManager(const std::vector<LedStripConfig>& configs)
{
    printf("[LedStripsManager] constructor\n");
    // policzenie wirtualnych pinów na potrzeby biblioteki Adafruit_NeoPXL8
    this->calculateVirtualLeds(configs);

    // pobranie tablicy pinów skonfigurowanych pasków led
    //std::unique_ptr<int8_t[]> pins = std::make_unique<int8_t[]>(this->strips.size());
    int8_t* pins = new int8_t[configs.size()]; // TODO Fix this
    for(int i = 0; i < configs.size(); i++)
        pins[i] = configs[i].getPinData();

    // utworzenie wirtualnego paska led składającego się z wielu pasków (od 1 do 8)
    this->pixels = std::make_unique<Adafruit_NeoPXL8>(this->virtualLedsEachStrip, pins, NEO_RGB + NEO_KHZ800);
    this->pixels->begin();

    // tworzenie klas LedStrip dla, każdej podanej konfiguracji
    for(auto config : configs) {
        //strips.push_back(std::make_unique<LedStrip>(config));
        StripId stripId = config.getStripId();
        int parsedId = static_cast<int>(config.getStripId());
        int virtualFirstLedNumber = this->getFirstStripLedNumber(stripId, configs);
        printf("virtualFirstLedNumber: %d\n", virtualFirstLedNumber);
        this->strips[parsedId] = std::make_unique<LedStrip>(config, virtualFirstLedNumber, this->pixels.get());
    }
}

LedStrip *LedStripsManager::getStrip(StripId stripId)
{
    int id = static_cast<int>(stripId);
    auto strip = this->strips[id].get();
    return strip;
}

void LedStripsManager::setStripLedColor(StripId id, int diodeNumber, uint8_t red, uint8_t green, uint8_t blue)
{
    // LedStrip* strip = this->getStrip(id);
    // int firstLedNumber = this->virtualLedsEachStrip * static_cast<int>(id);
    // int numberOfLeds = strip->getLedsCount();

    // int ledNumberToSetColor = this->getFirstStripLedNumber(id);
    // this->pixels->setPixelColor(diodeNumber, red, green, blue);

    LedStrip* strip = this->getStrip(id);
    strip->setLedColor(diodeNumber, red, green, blue);
}

void LedStripsManager::setStripBrightness(StripId id, uint8_t brightness)
{
    LedStrip* strip = this->getStrip(id);
    strip->setBrightness(brightness);
}

void LedStripsManager::show(StripId id)
{
    LedStrip* strip = this->getStrip(id);
    strip->show();
}

Adafruit_NeoPXL8 *LedStripsManager::getGlobalStrip()
{
    return this->pixels.get();
}

void LedStripsManager::calculateVirtualLeds(const std::vector<LedStripConfig>& configs)
{
    int longestStrip = 0;
    for(auto config : configs) {
        int stripLedsCount = config.getNumLeds();
        if(longestStrip < stripLedsCount) longestStrip = stripLedsCount;
    }

    this->virtualLedsEachStrip = longestStrip;
    this->totalVirtualLeds = longestStrip * configs.size();

    printf("[LedStripsManager] virtualLedsEachStrip(%d)\n", virtualLedsEachStrip);
    printf("[LedStripsManager] totalVirtualLeds(%d)\n", totalVirtualLeds);
}

int LedStripsManager::getFirstStripLedNumber(StripId id, const std::vector<LedStripConfig>& configs)
{
    int i = 0;
    for(auto config : configs) {
        if(config.getStripId() == id) return i * this->virtualLedsEachStrip;
        else i++;
    }

    printf("[LedStripsManager] getFirstStripLedNumber not found\n");

    return 0;
}
