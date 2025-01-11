add_subdirectory(./deps/Adafruit_NeoPixel)
add_subdirectory(./deps/Adafruit_NeoPixel_PicoSDK_support)
add_subdirectory(./deps/Adafruit_NeoPXL8)

#######################

#message("MESSAGE " ${PROJECT_SOURCE_DIR}/deps/Adafruit_NeoPixel)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/source/deps/Adafruit_NeoPixel)

add_executable(Application
        LedStrip.cpp
        SPISlave.cpp
        SolidColorAnimation.cpp
        AnimationManager.cpp
        LedStripsManager.cpp
        PacketFactory.cpp
        main.cpp
        )

target_include_directories(Application INTERFACE
        "/home/adasinho/pico-sdk/src/rp2_common/hardware_clocks/include"
)

# Pull in basic dependencies
target_link_libraries(Application pico_stdlib hardware_spi hardware_pio pico_malloc pico_mem_ops pico_neopixel pico_neopxl8 pico_multicore)
target_compile_definitions(Application PUBLIC ARDUINO_ARCH_RP2040)
target_compile_options(Application PUBLIC -g)

# create map/bin/hex file etc.
pico_add_extra_outputs(Application)

# add url via pico_set_program_url
example_auto_set_url(Application)

if (TARGET tinyusb_device)
        # enable usb output
        pico_enable_stdio_usb(Application 1)
elseif(PICO_ON_DEVICE)
        message(WARNING "not building SPI-Peripheral because TinyUSB submodule is not initialized in the SDK")
endif()
