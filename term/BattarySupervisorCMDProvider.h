#ifndef INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDPROVIDER_HPP_
#define INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDPROVIDER_HPP_

#include <CommandProvider.h>
#include <Array_mapping.h>
namespace InternalMonitoring {
namespace BatterySupervisor {

class BatterySupervisorCmdProvider : public CommandProvider {
public:
    uint8_t getPeriodicCommand() override;
    void onPollRoundEnd() override;
};

}
}
#endif /* INTERNALMONITORING_SEDP_BATTERYSUPERVISOR_COMMANDPROVIDER_HPP_ */
