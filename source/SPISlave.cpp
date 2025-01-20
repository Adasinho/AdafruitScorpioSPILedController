#include "SPISlave.hpp"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include <stdio.h>
#include <cstring>
#include <hardware/structs/spi.h>

//#include "Package.hpp"
#include "PacketFactory.hpp"
#include "CustomPackages.hpp"
#include "Logger.hpp"

template class SPISlave<Package>;

template <typename T>
SPISlave<T>::SPISlave(int rxPin, int txPin, int sckPin, int csPin, SPIInterface spi, int speed)
    : RX_PIN(rxPin), TX_PIN(txPin), SCK_PIN(sckPin), CS_PIN(csPin), CONNECTION_SPEED(speed) {

    this->spiInterface = getSPIInterface(spi);
    const int ONE_SECOND = 1000;

    stdio_init_all();
    sleep_ms(2 * ONE_SECOND);

    Logger::log(LogLevel::INFO, "[SPISlave] Define spi interface %d, with speed %d", spi, speed);

    spi_init(this->spiInterface, this->CONNECTION_SPEED);
    spi_set_slave(this->spiInterface, true);

    gpio_set_function(this->RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(this->SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(this->TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(this->CS_PIN, GPIO_FUNC_SPI);

    const int DATA_BITS = 8;

    spi_set_format(this->spiInterface, DATA_BITS, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
}

template <typename T>
void SPISlave<T>::receivingData(SpiRecvDataCallback<T> spiRecvDataCallback) {
    Logger::log(LogLevel::INFO, "[SPISlave] Start receiving data");

    while(true) {
        if(!spi_is_readable(this->spiInterface)) {
            // sleep_ms(1);
            continue;
        }

        const int REPEATED_TX_DATA = 0;
        const int RECEIVE_BYTES = 1;
        DataBuffer dataBuffer;

        Logger::log(LogLevel::INFO, "[SPISlave] SPI is readable");

        size_t bytesRead = spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, &dataBuffer.raw_data[0], RECEIVE_BYTES);
        if(bytesRead != 1) {
            Logger::log(LogLevel::ERROR, "[SPISlave] Failed to read operation byte");
            continue;
        }

        Operation operation = static_cast<Operation>(dataBuffer.raw_data[0]);
        Logger::log(LogLevel::INFO, "[SPISlave] Operation: %d", operation);

        int packetSize = PacketFactory::getPacketSize(operation);
        if(packetSize == 0) {
            Logger::log(LogLevel::ERROR, "[SPISlave] Unknown operation or invalid packet size");
            continue;
        }

        bytesRead = spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, &dataBuffer.raw_data[1], packetSize - 1);
        if(bytesRead != packetSize - 1) {
            Logger::log(LogLevel::ERROR, "[SPISlave] Failed to read full package, expected %d, read %d", packetSize, bytesRead);
            continue;
        }

        Package* package = nullptr;

        switch(operation) {
            case SET_DIODE_COLOR:
                package = new SetColorPackage();
                memcpy(package, &dataBuffer.setColorPackage, sizeof(SetColorPackage));
                break;
            case SET_BRIGHTNES:
                package = new SetBrightnessPackage();
                memcpy(package, &dataBuffer.setBrightnessPackage, sizeof(SetBrightnessPackage));
                break;
            case SET_STRIP_ANIMATION:
                package = new SetStripAnimationPackage();
                memcpy(package, &dataBuffer.setStripAnimationPackage, sizeof(SetStripAnimationPackage));
                break;
            case SET_STRIP_SOLID_COLOR:
                package = new SetStripSolidColorPackage();
                memcpy(package, &dataBuffer.setStripSolidColorPackage, sizeof(SetStripSolidColorPackage));
                break;
            default:
                Logger::log(LogLevel::WARNING, "[SPISlave] Unknown operation\n");
                continue;
        }

        if(package != nullptr) {
            spiRecvDataCallback(package);
            delete package;
            package = nullptr;
        }
    }
}

template <typename T>
spi_inst_t* SPISlave<T>::getSPIInterface(SPIInterface spi) {
    switch(spi) {
        case SPI0:
            return spi0;
        case SPI1:
            return spi1;
        default:
            return NULL;
    }
}