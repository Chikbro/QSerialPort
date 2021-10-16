
#ifndef INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDFACTORY_HPP_
#define INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDFACTORY_HPP_

#include <CommandProvider.h>
#include <Command.h>
#include <CommandFactory.h>

namespace InternalMonitoring {
namespace BatterySupervisor {

class BatterySupervisorCmdFactory
{
public:
    Command* getCommand(uint8_t cmdId);
};

}
}
#endif /* INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDFACTORY_HPP_ */
