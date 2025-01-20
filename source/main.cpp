#include "SPISlave.hpp"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/sem.h"
#include "hardware/timer.h"

//#include "Adafruit_NeoPixel.h"

#include <Adafruit_NeoPXL8.h>

#include "Package.hpp"
#include "Operations.hpp"
#include "CustomPackages.hpp"

#define PIN        16         // Pin GPIO, do którego podłączone są LED-y
#define NUMPIXELS  60          // Liczba diod LED w pasku

#include <memory>

#include "LedStrip.hpp"
#include "LedStripConfig.hpp"
#include "LedStripsManager.hpp"
#include "AnimationManager.hpp"
#include "SolidColorAnimation.hpp"
#include "Utils.hpp"
#include "Logger.hpp"

const LedStripConfig led_strip_1_config(StripId::STRIP_1, 20, 16); // STRIP 1
const LedStripConfig led_strip_2_config(StripId::STRIP_2, 20, 17); // STRIP 2
const LedStripConfig led_strip_3_config(StripId::STRIP_3, 20, 18); // STRIP 3
const LedStripConfig led_strip_4_config(StripId::STRIP_4, 20, 19); // STRIP 4
const LedStripConfig led_strip_5_config(StripId::STRIP_5, 20, 20); // STRIP 5
const LedStripConfig led_strip_6_config(StripId::STRIP_6, 20, 21); // STRIP 6
const LedStripConfig led_strip_7_config(StripId::STRIP_7, 20, 22); // STRIP 7
const LedStripConfig led_strip_8_config(StripId::STRIP_8, 20, 23); // STRIP 8

std::unique_ptr<LedStripsManager> manager;
std::unique_ptr<AnimationManager> animationManager;

// std::unique_ptr<LedStrip> led_strip_1 = std::make_unique<LedStrip>(led_strip_1_config);
// std::unique_ptr<LedStrip> led_strip_2 = std::make_unique<LedStrip>(led_strip_2_config);

void setupConfiguration() {
    Logger::log(LogLevel::INFO, "[Main] setupConfiguration");

    const std::vector<LedStripConfig> configs = {
        led_strip_1_config,
        led_strip_2_config,
        led_strip_3_config,
        led_strip_4_config,
        led_strip_5_config,
        led_strip_6_config,
        led_strip_7_config,
        led_strip_8_config
    };

    manager = std::make_unique<LedStripsManager>(configs);
    Adafruit_NeoPXL8* pixels = manager->getGlobalStrip();
    animationManager = std::make_unique<AnimationManager>(pixels);
}

//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

// For the Feather RP2040 SCORPIO, use this list:
// int8_t pins[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };
// Adafruit_NeoPXL8 pixels(NUMPIXELS, pins, NEO_RGB + NEO_KHZ800);

void recvDataCallback(Package* package) {
    if(package->operation == SET_DIODE_COLOR) {
        SetColorPackage* setColorPackage = reinterpret_cast<SetColorPackage*>(package);
        //Logger::log(LogLevel::DEBUG, "[Callback] Odebrano pakiet set color");
        // Logger::log(LogLevel::DEBUG, "Strip number: %d, Diode number: %d, Color(%d, %d, %d)",
        //     setColorPackage->led_strip_number,
        //     setColorPackage->led_diode_number,
        //     setColorPackage->red,
        //     setColorPackage->green,
        //     setColorPackage->blue
        // );

        // pixels.setPixelColor(setColorPackage->led_diode_number, pixels.Color(setColorPackage->red, setColorPackage->green, setColorPackage->blue));
        // pixels.show();
    } else if (package->operation == SET_BRIGHTNES) {
        SetBrightnessPackage* setBrightnessPackage = reinterpret_cast<SetBrightnessPackage*>(package);

        if(Utils::validStripId(setBrightnessPackage->led_strip_number)) {
            StripId stripId = static_cast<StripId>(setBrightnessPackage->led_strip_number);
            LedStrip* strip = manager->getStrip(stripId);
            uint8_t brightness = setBrightnessPackage->brightness;

            strip->setBrightness(brightness);
        }

        // Logger::log(LogLevel::DEBUG, "Odebrano pakiet set brightness");
        // Logger::log(LogLevel::DEBUG, "[Callback] Strip number: %d, brightness: %d",
        //     setBrightnessPackage->led_strip_number,
        //     setBrightnessPackage->brightness
        // );
        // pixels.setBrightness(setBrightnessPackage->brightness);
        // pixels.show();
    } else if (package->operation == SET_STRIP_SOLID_COLOR) {
        SetStripSolidColorPackage* setStripSolidcolorPackage = reinterpret_cast<SetStripSolidColorPackage*>(package);

        if(Utils::validStripId(setStripSolidcolorPackage->led_strip_number)) {
            StripId stripId = static_cast<StripId>(setStripSolidcolorPackage->led_strip_number);
            LedStrip* strip = manager->getStrip(stripId);
            Color targetColor(
                setStripSolidcolorPackage->red,
                setStripSolidcolorPackage->green,
                setStripSolidcolorPackage->blue
            );
            uint8_t speed = setStripSolidcolorPackage->speed;

            // Logger::log(LogLevel::DEBUG, "[Callback] Set Strip %d solid color: %d, %d, %d",
            //     stripId,
            //     setStripSolidcolorPackage->red,
            //     setStripSolidcolorPackage->green,
            //     setStripSolidcolorPackage->blue
            // );

            animationManager->playAnimation(stripId, std::make_unique<SolidColorAnimation>(strip, targetColor, speed));
        } else {
            Logger::log(LogLevel::WARNING, "[MAIN] Can't run animation in invalid strip number: %d", setStripSolidcolorPackage->led_strip_number);
        }
    } else {
        Logger::log(LogLevel::WARNING, "[Callback] Odebrano nieznany pakiet");
    }   
}

semaphore_t semafor;

void core1_entry() {
    // wait for signal
    //sem_acquire_blocking(&semafor);

    ///

    // release semaphore
    //sem_release(&semafor);

    sleep_ms(1000);

    Logger::log(LogLevel::INFO, "Core 1 running");

    // int8_t pins[8] = { 16, 17, 18, 19, 20, 21, 22, 23 };
    // std::unique_ptr<Adafruit_NeoPXL8> pixels = std::make_unique<Adafruit_NeoPXL8>(60, pins, NEO_RGB + NEO_KHZ800);
    // if(!pixels->begin())
    // {
    //     Logger::log(LogLevel::ERROR, "Can't create NeoPXL8");
    // } else {
    //     pixels->setBrightness(255);
    //     pixels->setPixelColor(1, 24, 55, 120);
    //     pixels->show();
    // }

    setupConfiguration();

    while(true) {
        animationManager->update();
        sleep_ms(10);
    }
}

int main() {
    stdio_init_all();

    // initial semaphore
    sem_init(&semafor, 0, 1);
    // start second thread
    multicore_launch_core1(core1_entry);
    
    const int RX = 8;
    const int TX = 15;
    const int SCK = 14;
    const int CS = 25;
    const int SPEED = 1000000; // 1MHz
    
    // pixels.begin();           // Rozpocznij działanie NeoPixel
    // pixels.show();            // Upewnij się, że wszystkie LED-y są wyłączone na początku
    // pixels.clear();

    SPISlave<Package> spi(RX, TX, SCK, CS, SPI1, SPEED);
    spi.receivingData(recvDataCallback);

    Logger::log(LogLevel::INFO, "[main] After spi class");

    return 0;
}