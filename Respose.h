#ifndef SBIP_RESPONSECODE_HPP_
#define SBIP_RESPONSECODE_HPP_

#include "stdint.h"

namespace SBIP {

enum class Response : uint8_t {
    Ok = 0x00,
    NoSuchCommand = 0x01,
    GeneralError = 0x02,
    InvalidData = 0x03,
    DeviceBusy = 0x04
};

}



#endif /* SBIP_RESPONSECODE_HPP_ */
