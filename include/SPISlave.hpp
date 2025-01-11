#include "hardware/spi.h"

#include "CustomPackages.hpp"

enum SPIInterface {
    SPI0 = 0,
    SPI1 = 1
};

// enum Operation {
//     SET_DIODE_COLOR = 0,
//     SET_BRIGHTNES = 1,
//     SET_STRIP_ANIMATION = 2
// };

// enum Animation {
//     TEST1 = 0
// };

// struct Package {
//     uint8_t operation;
// };

// struct SetColorPackage : public Package {
//     uint8_t led_strip_number;
//     uint8_t led_diode_number;
//     uint8_t red;
//     uint8_t green;
//     uint8_t blue;
// };

// struct SetBrightnessPackage : public Package {
//     uint8_t led_strip_number;
//     uint8_t brightness;
// };

// struct SetStripAnimationPackage : public Package {
//     uint8_t led_strip_number;
//     uint8_t animation_id;
// };

// struct AnimationState {
//     bool isAnimating;
//     Animation animationId;
//     bool isFinished;
// };

union DataBuffer {
    uint8_t raw_data[sizeof(SetColorPackage)]; // biggest structure
    Package package;
    SetColorPackage setColorPackage;
    SetBrightnessPackage setBrightnessPackage;
    SetStripAnimationPackage setStripAnimationPackage;
    SetStripSolidColorPackage setStripSolidColorPackage;
};

//typedef void (*SpiRecvDataCallback)(Package*);

template <typename T>
using SpiRecvDataCallback = void (*)(T*);

template <typename T>
class SPISlave {
    public:
    SPISlave(int rxPin, int txPin, int sckPin, int csPin, SPIInterface spi, int speed);
    void receivingData(SpiRecvDataCallback<T> spiRecvDataCallback);
    
    //Package* getOperationPackage(DataBuffer& dataBuffer);
    //static bool timer_callback(struct repeating_timer* t);
    
    private:
    const int RX_PIN;
    const int TX_PIN;
    const int SCK_PIN;
    const int CS_PIN;

    spi_inst_t* spiInterface;
    const int CONNECTION_SPEED;

    const int BUF_LEN = 128;
    static const int NUM_PIXELS = 8;
    static const int NUM_LEDS_ON_STRIP = 58;

    spi_inst_t* getSPIInterface(SPIInterface spi);
};