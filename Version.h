#ifndef VERSION_H
#define VERSION_H

#include <cstdint>

namespace CommonTypes {
struct  Version {
    uint8_t minor;
    uint8_t major;

    bool operator==(const Version& other) const {
        return minor == other.minor && major == other.major;
    }
    bool operator>(const Version& other) const {
        if(major == other.major) {
            return minor > other.minor;
        }
        return major > other.major;
    }
    bool operator>=(const Version& other) const {
        return *this > other || *this == other;
    }
    bool operator!=(const Version& other) const {
        return !(*this == other);
    }
    bool operator<(const Version& other) const {
        return other > *this;
    }
    bool operator<=(const Version& other) const {
        return other >= *this;
    }
};
}

#endif
