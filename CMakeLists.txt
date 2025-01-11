
cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_COMPILER_WORKS)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Import Pico SDK
include(pico_sdk_import.cmake)

project(adafruit_feather_scorpio_spi_slave C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
        message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

include(example_auto_set_url.cmake)

#FetchContent_Declare(
  #adafruit_neopixel
  #GIT_REPOSITORY https://github.com/adafruit/Adafruit_NeoPixel.git
  #GIT_TAG        master # lub konkretny tag/commit
#)

#FetchContent_MakeAvailable(adafruit_neopixel)

#add_library(adafruit_neopixel STATIC ${adafruit_neopixel_SOURCE_DIR}/Adafruit_NeoPixel.cpp) # Lub lista plików źródłowych
#message("TEST: ${PICO_INCLUDE_DIRS}")
#target_include_directories(adafruit_neopixel PUBLIC
    #${adafruit_neopixel_SOURCE_DIR}/include # Ścieżka do plików nagłówkowych Adafruit_NeoPixel
    #${PICO_INCLUDE_DIRS}
    #"/home/adasinho/pico-sdk/src/rp2_common/hardware_pio/include"
#)
#target_link_libraries(adafruit_neopixel PUBLIC pico_stdlib) # Dodaj zależność od biblioteki pico
#target_compile_definitions(adafruit_neopixel PUBLIC ARDUINO_ARCH_RP2040)

#example_auto_set_url(adafruit_neopixel)

# Import Adafruit_NeoPXL8
#include(adafruit_neopxl8_import.cmake)
#add_library(Adafruit_NeoPXL8 STATIC IMPORTED)
#include(adafruit_neopixel_import.cmake)

#message(STATUS "Ścieżka do pobranego projektu: ${adafruit_neopxl8_SOURCE_DIR}")
#include_directories(${adafruit_neopxl8_SOURCE_DIR}/) # Dodajemy ścieżkę do głównego katalogu biblioteki
#include_directories(${ADAFRUIT_NEOPIXEL_PATH}/) # Dodajemy ścieżkę do głównego katalogu biblioteki
#include_directories(${adafruit_zerodma_SOURCE_DIR}/) # Dodajemy ścieżkę do głównego katalogu biblioteki

# Add source folders
add_subdirectory(source)
#add_subdirectory(SPI-Peripheral)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )
        