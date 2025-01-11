#ifndef CUSTOM_PACKAGE_HPP
#define CUSTOM_PACKAGE_HPP

#include "Package.hpp"

struct SetColorPackage : public Package {
    uint8_t led_strip_number;
    uint8_t led_diode_number;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct SetBrightnessPackage : public Package {
    uint8_t led_strip_number;
    uint8_t brightness;
};

struct SetStripAnimationPackage : public Package {
    uint8_t led_strip_number;
    uint8_t animation_id;
};

struct SetStripSolidColorPackage : public Package {
    uint8_t led_strip_number;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t speed;
};

#endif // CUSTOM_PACKAGE_HPP