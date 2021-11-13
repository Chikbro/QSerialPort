#include "Version.h"
#include "Manufacturer.h"
#include <array>
#include <QMainWindow>

namespace CommonTypes 	{

using HardwareVersion = std::array<char, 32>;

struct DevicePassport {
    Version protocolVersion;
    Version softwareVersion;
    HardwareVersion hardwareVersion;
    uint8_t deviceType;
    CommonTypes::Manufacturer organizationCode;
    uint64_t serialNumber;
    uint32_t productionDate;
};
}
