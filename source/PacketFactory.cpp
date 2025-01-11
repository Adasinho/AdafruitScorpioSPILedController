#include "PacketFactory.hpp"

std::unique_ptr<Package> PacketFactory::createPacket(Operation operation) {
    switch (operation) {
        case Operation::SET_DIODE_COLOR:
            return std::make_unique<SetColorPackage>();
        case Operation::SET_BRIGHTNES:
            return std::make_unique<SetBrightnessPackage>();
        case Operation::SET_STRIP_ANIMATION:
            return std::make_unique<SetStripAnimationPackage>();
        case Operation::SET_STRIP_SOLID_COLOR:
            return std::make_unique<SetStripSolidColorPackage>();
        default:
            return nullptr;
    }
}

size_t PacketFactory::getPacketSize(Operation operation) {
    switch (operation) {
        case Operation::SET_DIODE_COLOR:
            return sizeof(SetColorPackage);
        case Operation::SET_BRIGHTNES:
            return sizeof(SetBrightnessPackage);
        case Operation::SET_STRIP_ANIMATION:
            return sizeof(SetStripAnimationPackage);
        case Operation::SET_STRIP_SOLID_COLOR:
            return sizeof(SetStripSolidColorPackage);
        default:
            return 0; // Lub rzuć wyjątek
    }
}