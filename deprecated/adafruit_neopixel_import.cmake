# This is a copy of <ADAFRUIT_NEOPIXEL_PATH>/external/pico_sdk_import.cmake

# This can be dropped into an external project to help locate this SDK
# It should be include()ed prior to project()

if (DEFINED ENV{ADAFRUIT_NEOPIXEL_PATH} AND (NOT ADAFRUIT_NEOPIXEL_PATH))
    set(ADAFRUIT_NEOPIXEL_PATH $ENV{ADAFRUIT_NEOPIXEL_PATH})
    message("Using ADAFRUIT_NEOPIXEL_PATH from environment ('${ADAFRUIT_NEOPIXEL_PATH}')")
endif ()

if (DEFINED ENV{ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT} AND (NOT ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT))
    set(ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT $ENV{ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT})
    message("Using ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT from environment ('${ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT}')")
endif ()

if (DEFINED ENV{ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH} AND (NOT ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH))
    set(ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH $ENV{ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH})
    message("Using ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH from environment ('${ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH}')")
endif ()

set(ADAFRUIT_NEOPIXEL_PATH "${ADAFRUIT_NEOPIXEL_PATH}" CACHE PATH "Path to the Raspberry Pi Pico SDK")
set(ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT "${PICO_SDK_FETCH_FROM_GIT}" CACHE BOOL "Set to ON to fetch copy of SDK from git if not otherwise locatable")
set(ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH "${ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH}" CACHE FILEPATH "location to download SDK")

if (NOT ADAFRUIT_NEOPIXEL_PATH)
        include(FetchContent)
        set(FETCHCONTENT_BASE_DIR_SAVE ${FETCHCONTENT_BASE_DIR})
        if (ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH)
            get_filename_component(FETCHCONTENT_BASE_DIR "${ADAFRUIT_NEOPIXEL_FETCH_FROM_GIT_PATH}" REALPATH BASE_DIR "${CMAKE_SOURCE_DIR}")
        endif ()
        # GIT_SUBMODULES_RECURSE was added in 3.17
        if (${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.17.0")
            FetchContent_Declare(
                    adafruit_neopixel
                    GIT_REPOSITORY https://github.com/adafruit/Adafruit_NeoPixel.git
                    GIT_TAG master
                    GIT_SUBMODULES_RECURSE FALSE
            )
        else ()
            FetchContent_Declare(
                    adafruit_neopixel
                    GIT_REPOSITORY https://github.com/adafruit/Adafruit_NeoPixel.git
                    GIT_TAG master
            )
        endif ()

        if (NOT adafruit_neopixel)
            message("Downloading Raspberry Pi Pico SDK")
            FetchContent_Populate(adafruit_neopixel)
            set(ADAFRUIT_NEOPIXEL_PATH ${adafruit_neopixel_SOURCE_DIR})
        endif ()
        set(FETCHCONTENT_BASE_DIR ${FETCHCONTENT_BASE_DIR_SAVE})
endif ()

get_filename_component(ADAFRUIT_NEOPIXEL_PATH "${ADAFRUIT_NEOPIXEL_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
if (NOT EXISTS ${ADAFRUIT_NEOPIXEL_PATH})
    message(FATAL_ERROR "Directory '${ADAFRUIT_NEOPIXEL_PATH}' not found")
endif ()

#set(ADAFRUIT_NEOPIXEL_INIT_CMAKE_FILE ${ADAFRUIT_NEOPIXEL_PATH}/adafruit_neopixel_init.cmake)
#if (NOT EXISTS ${ADAFRUIT_NEOPIXEL_INIT_CMAKE_FILE})
    #message(FATAL_ERROR "Directory '${ADAFRUIT_NEOPIXEL_PATH}' does not appear to contain the Raspberry Pi Pico SDK")
#endif ()

set(ADAFRUIT_NEOPIXEL_PATH ${ADAFRUIT_NEOPIXEL_PATH} CACHE PATH "Path to the Raspberry Pi Pico SDK" FORCE)

#include(${ADAFRUIT_NEOPIXEL_INIT_CMAKE_FILE})

include_directories("/home/adasinho/pico-sdk/src/rp2_common/hardware_pio/include")