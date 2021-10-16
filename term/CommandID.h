#ifndef INTERNALMONITORING_SEDP_INVERTER_COMMANDID_HPP_
#define INTERNALMONITORING_SEDP_INVERTER_COMMANDID_HPP_
#include <CommandFactory.h>
namespace InternalMonitoring {
namespace Inverter {

enum CommandId {
    GetPassport = 0x00,
    SetPassport = 0x01,
    GetParams = 0x02,
    GetStatus = 0x04,
    GetSettings = 0x05,
    SetSettings = 0x06,
    SetGroupControl = 0x09,
    SetControl = 0xA
};

}
}

#endif /* INTERNALMONITORING_SEDP_INVERTER_COMMANDID_HPP_ */
