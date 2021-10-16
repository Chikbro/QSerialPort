#ifndef INTERNALMONITORING_DEVICEID_HPP_
#define INTERNALMONITORING_DEVICEID_HPP_

#include <cstdint>

namespace InternalMonitoring {

struct DeviceId {
    uint8_t address;
    uint8_t group;
};

}
#endif /* INTERNALMONITORING_DEVICEID_HPP_ */
