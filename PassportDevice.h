#include "Version.h"
#include "Manufacturer.h"
#include <array>
#include <QMainWindow>

namespace CommonTypes 	{

using HardwareVersion = std::array<char, 32>;

struct DevicePassport {
    QByteArray protocolVersion;
    QByteArray softwareVersion;
    QByteArray hardwareVersion;
    QByteArray deviceType;
    QByteArray organizationCode;
    QByteArray serialNumber;
    QByteArray productionDate;

//    Version protocolVersion;
//    Version softwareVersion;
//    HardwareVersion hardwareVersion;
//    uint8_t deviceType;
//    CommonTypes::Manufacturer organizationCode;
//    uint64_t serialNumber;
//    uint32_t productionDate;
};
}
