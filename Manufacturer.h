#ifndef MANUFACTURER_H
#define MANUFACTURER_H

#include <stdint.h>

namespace CommonTypes {
    // Производитель устройства
    enum class Manufacturer : uint8_t {
        // Ирбис-Т
        IrbisT = 0,
        // Штиль энерго
        ShtylEnergo = 1
    };
}

#endif // MANUFACTURER_H
