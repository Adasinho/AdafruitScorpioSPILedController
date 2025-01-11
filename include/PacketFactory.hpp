#ifndef PACKET_FACTORY_HPP
#define PACKET_FACTORY_HPP

#include "Package.hpp"
#include "CustomPackages.hpp"
#include "Operations.hpp"
#include <memory>

class PacketFactory {
public:
    static std::unique_ptr<Package> createPacket(Operation operation);
    static size_t getPacketSize(Operation operation);
};

#endif // PACKET_FACTORY_HPP