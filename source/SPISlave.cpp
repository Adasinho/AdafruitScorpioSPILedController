#include "SPISlave.hpp"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#include <stdio.h>
#include <cstring>
#include <hardware/structs/spi.h>

//#include "Package.hpp"
#include "PacketFactory.hpp"
#include "CustomPackages.hpp"

template class SPISlave<Package>;

template <typename T>
SPISlave<T>::SPISlave(int rxPin, int txPin, int sckPin, int csPin, SPIInterface spi, int speed)
    : RX_PIN(rxPin), TX_PIN(txPin), SCK_PIN(sckPin), CS_PIN(csPin), CONNECTION_SPEED(speed) {

    this->spiInterface = getSPIInterface(spi);
    const int ONE_SECOND = 1000;

    stdio_init_all();
    sleep_ms(2 * ONE_SECOND);

    printf("[SPISlave] Define spi interface %d, with speed %d \n", spi, speed);

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
    printf("[SPISlave] Start receiving data\n");

    while(true) {
        if(spi_is_readable(this->spiInterface)) {
            const int REPEATED_TX_DATA = 0;
            const int RECEIVE_BYTES = 1;
            DataBuffer dataBuffer;

            spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, &dataBuffer.raw_data[0], RECEIVE_BYTES);

            Operation operation = static_cast<Operation>(dataBuffer.raw_data[0]);
            printf("[SPISlave] Operation: %d \n", operation);
            int packetSize = PacketFactory::getPacketSize(operation);

            spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, &dataBuffer.raw_data[1], packetSize - 1);

            Package* package;

            switch(operation) {
                case SET_DIODE_COLOR:
                    package = &dataBuffer.setColorPackage;
                    break;
                case SET_BRIGHTNES:
                    package = &dataBuffer.setBrightnessPackage;
                    break;
                case SET_STRIP_ANIMATION:
                    package = &dataBuffer.setStripAnimationPackage;
                    break;
                case SET_STRIP_SOLID_COLOR:
                    package = &dataBuffer.setStripSolidColorPackage;
                    break;
                default:
                    printf("[SPISlave] Unknown operation\n");
            }

            //Package* package = getOperationPackage(dataBuffer);
            spiRecvDataCallback(package);
        }
    }

    // while(true) {
    //     if(spi_is_readable(this->spiInterface)) {
    //         const int REPEATED_TX_DATA = 0;
    //         const int RECEIVE_BYTES = 10;
    //         DataBuffer dataBuffer;

    //         // TODO Zmienić aby odbierało dane tylko raz i aby pobierało zawsze tyle
    //         //      bajtów ile ma największy pakiet (tak jak było wcześniej)

    //         // printf("Checkpoint 1\n");

    //         // uint8_t operationByte;
    //         // spi_read_blocking(this->spiInterface, 0, &operationByte, 1);
    //         // printf("Checkpoint 2\n");
    //         // Operation operation = static_cast<Operation>(operationByte);
    //         // printf("Checkpoint 3\n");

    //         // size_t packageSize = PacketFactory::getPacketSize(operation);
    //         // printf("Checkpoint 4\n");

    //         // std::unique_ptr<Package> package = PacketFactory::createPacket(operation);
    //         // printf("Checkpoint 5\n");

    //         // if(package) {
    //         //     if(packageSize > sizeof(operation)) {
    //         //         spi_read_blocking(this->spiInterface, 0, reinterpret_cast<uint8_t*>(package.get()) + sizeof(operation), packageSize - sizeof(operation));
    //         //         printf("Checkpoint 6\n");
    //         //     }
    //         // }
            
    //         Package data;

    //         spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, &dataBuffer.raw_data[0], RECEIVE_BYTES);
    //         //spi_read_blocking(this->spiInterface, REPEATED_TX_DATA, reinterpret_cast<uint8_t*>(&data), sizeof(SetColorPackage));
            
    //         //Package* package = getOperationPackage(dataBuffer);
    //         //spiRecvDataCallback(package);
    //         spiRecvDataCallback(&data);
    //         //spiRecvDataCallback(package.get());
    //     }
    // }
}

// Package* SPISlave<T>::getOperationPackage(DataBuffer& dataBuffer) {
//     switch(dataBuffer.package.operation) {
//         int bytesToRead;
//         int repeatedTxData;
//         case SET_DIODE_COLOR:
//             bytesToRead = sizeof(SetColorPackage) - 1;
//             repeatedTxData = 1;

//             spi_read_blocking(this->spiInterface, repeatedTxData, &dataBuffer.raw_data[1], bytesToRead);

//             return &dataBuffer.setColorPackage;
//         case SET_BRIGHTNES:
//             bytesToRead = 2;
//             repeatedTxData = 1;

//             spi_read_blocking(this->spiInterface, repeatedTxData, &dataBuffer.raw_data[1], bytesToRead);

//             return &dataBuffer.setBrightnessPackage;
//         case SET_STRIP_ANIMATION:
//             bytesToRead = sizeof(SetStripAnimationPackage) - 1;
//             repeatedTxData = 1;

//             spi_read_blocking(this->spiInterface, repeatedTxData, &dataBuffer.raw_data[1], bytesToRead);

//             return &dataBuffer.setStripAnimationPackage;
//         default:
//             printf("Unknown operation code.\n");
//     }
// }

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

// bool SPISlave::timer_callback(struct repeating_timer* t) {
//     for(int i = 0; i < NUM_PIXELS; i++) {
//         if (animationState[i].isAnimating) {
//             if(animationState[i].isFinished) {
//                 animationState[i].isAnimating = false;
//             } else {
//                 switch(animationState[i].animationId) {
//                     case TEST1: {
//                         for(int j = 0; j < NUM_LEDS_ON_STRIP; j++) {
//                             // Ustaw kolor diody j na podstawie numeru diody, czasu i stanu animacji
//                             uint8_t red = (j * 255 / NUM_LEDS_ON_STRIP) + (to_ms_since_boot(get_absolute_time()) / 100) % 255;
//                             uint8_t green = (255 - j * 255 / NUM_LEDS_ON_STRIP) + (to_ms_since_boot(get_absolute_time()) / 150) % 255;
//                             uint8_t blue = (j * 128 / NUM_LEDS_ON_STRIP) + (to_ms_since_boot(get_absolute_time()) / 200) % 255;
//                             // Wyślij dane do paska LED (zakładam, że masz funkcję `setLedColor`)
//                             setLedColor(i, j, red, green, blue); 
//                         }
//                         break;
//                     }
//                 }
//             }
//         }
//     }

//     return true;
// }