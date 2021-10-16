#ifndef DEBUGMONITORING_SLAVE_COMMANDFACTORY_HPP_
#define DEBUGMONITORING_SLAVE_COMMANDFACTORY_HPP_

#include <Command.h>
#include <CommandID.h>

namespace DebugMonitoring {
namespace Slave {

class CommandFactory
{
public:
    virtual InternalMonitoring::Command* getCommand(InternalMonitoring::Inverter::CommandId cmd) = 0;
};

}
}
#endif /* DEBUGMONITORING_SLAVE_COMMANDFACTORY_HPP_ */
