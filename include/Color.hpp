#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

class Color {
public:
    Color() {}
    Color(uint8_t r, uint8_t g, uint8_t b)
        : r(r), g(g), b(b) {

    }

    uint8_t getRed() { return r; }
    uint8_t getGreen() { return g; }
    uint8_t getBlue() { return b; }

    void setColor(uint8_t red, uint8_t green, uint8_t blue) {
        this->r = red;
        this->g = green;
        this->b = blue;
    }

    // Operator ==
    bool operator==(const Color& other) const {
        return (r == other.r) && (g == other.g) && (b == other.b);
    }

    // Operator !=
    bool operator!=(const Color& other) const {
        return !(*this == other);
    }

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

#endif // COLOR_HPP