include(FetchContent)

FetchContent_Declare(
  adafruit_neopxl8
  GIT_REPOSITORY https://github.com/adafruit/Adafruit_NeoPXL8.git
  GIT_TAG        master # lub konkretny tag/commit
)

FetchContent_MakeAvailable(adafruit_neopxl8)

#set(ADAFRUIT_NEOPXL8_PATH ${Adafruit_NeoPixel_SOURCE_DIR})

#get_filename_component(ADAFRUIT_NEOPXL8_PATH "${ADAFRUIT_NEOPXL8_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
#if (NOT EXISTS ${ADAFRUIT_NEOPXL8_PATH})
    #message(FATAL_ERROR "Directory '${ADAFRUIT_NEOPXL8_PATH}' not found")
#endif ()

#set(ADAFRUIT_NEOPXL8_SOURCE_FILE ${ADAFRUIT_NEOPXL8_PATH}/Adafruit_NeoPXL8.cpp)
#if (NOT EXISTS ${ADAFRUIT_NEOPXL8_SOURCE_FILE})
    #message(FATAL_ERROR "Directory '${ADAFRUIT_NEOPXL8_PATH}' does not appear to contain the Adafruit_NeoPXL8 source file")
#endif ()

#set(ADAFRUIT_NEOPXL8_INCLUDE_FILE ${ADAFRUIT_NEOPXL8_PATH}/Adafruit_NeoPXL8.h)
#if (NOT EXISTS ${ADAFRUIT_NEOPXL8_INCLUDE_FILE})
    #message(FATAL_ERROR "Directory '${ADAFRUIT_NEOPXL8_PATH}' does not appear to contain the Adafruit_NeoPXL8 include file")
#endif ()

#set(ADAFRUIT_NEOPXL8_PATH ${ADAFRUIT_NEOPXL8_PATH} CACHE PATH "Path to the Adafruit_NeoPXL8 SDK" FORCE)

#message(STATUS "Ścieżka do pobranego projektu: ${adafruit_neopixel_SOURCE_DIR}")
#include_directories(${adafruit_neopixel_SOURCE_DIR}/) # Dodajemy ścieżkę do głównego katalogu biblioteki


### Add dependencies
FetchContent_Declare(
  adafruit_neopixel
  GIT_REPOSITORY https://github.com/adafruit/Adafruit_NeoPixel.git
  GIT_TAG        master # lub konkretny tag/commit
)

FetchContent_MakeAvailable(adafruit_neopixel)

FetchContent_Declare(
  adafruit_zerodma
  GIT_REPOSITORY https://github.com/adafruit/Adafruit_ZeroDMA.git
  GIT_TAG        master # lub konkretny tag/commit
)

FetchContent_MakeAvailable(adafruit_zerodma)

FetchContent_Declare(
  sdfat
  GIT_REPOSITORY https://github.com/adafruit/SdFat.git
  GIT_TAG        master # lub konkretny tag/commit
)

FetchContent_MakeAvailable(sdfat)

# Import Pico SDK
include(pico_sdk_import.cmake)

include(${PICO_SDK_INIT_CMAKE_FILE})

add_library(adafruit_neopixel STATIC ${adafruit_neopixel_SOURCE_DIR}/Adafruit_NeoPixel.cpp) # Lub lista plików źródłowych
target_include_directories(adafruit_neopixel PUBLIC
    ${adafruit_neopixel_SOURCE_DIR} # Ścieżka do plików nagłówkowych Adafruit_NeoPixel
    ${PICO_INCLUDE_DIRS}
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_pio/include"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_spi/include/"
    "/home/adasinho/pico-sdk/src/boards/include/boards"
    "/home/adasinho/pico-sdk/src/rp2040/hardware_structs/include"
    "/home/adasinho/pico-sdk/src/rp2040/hardware_regs/include/hardware"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_base/include"
    "/home/adasinho/pico-sdk/src/rp2040/hardware_regs/include"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_base/include"
    "/home/adasinho/pico-sdk/src/rp2350/hardware_regs/include"
    "/home/adasinho/pico-sdk/src/rp2350/hardware_structs/include"
    "/home/adasinho/pico-sdk/src/common/pico_binary_info/include"
    "/home/adasinho/pico-sdk/src/common/pico_stdlib_headers/include"
    "/home/adasinho/pico-sdk/src/host/pico_stdio/include"
    "/home/adasinho/pico-sdk/src/common/pico_time/include"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_timer/include"
    "/home/adasinho/pico-sdk/src/host/hardware_gpio/include"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_uart/include"
    "/home/adasinho/pico-sdk/src/rp2_common/hardware_resets/include"
)
target_link_libraries(adafruit_neopixel PUBLIC pico_stdlib) # Dodaj zależność od biblioteki pico
target_compile_definitions(adafruit_neopixel PUBLIC ARDUINO_ARCH_RP2040) 

example_auto_set_url(adafruit_neopixel)