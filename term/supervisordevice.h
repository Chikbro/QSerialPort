#include <CommandProvider.h>
#include <DeviceID.h>
#include<DeviceCategory.h>
#include <BattarySupervisorCMDProvider.h>
#include <BattarySupervisorCMDFactory.h>
#include <SabParams.h>
namespace InternalMonitoring {
namespace BatterySupervisor {
namespace MonitoredData {


class SupervisorDevice:public CommandProvider
{
public:
    SupervisorDevice(QAbstractEventDispatcher& dispatcher, uint8_t noResponseMaxCount, CommandProvider& immCmdProvider,
    MonitoredData::BatterySupervisor::BatterySupervisorData& devices);
private:
    BatterySupervisorCmdProvider _cmdProvider;
    BatterySupervisorCmdFactory _cmdFactory;
    MonitoredData::BatterySupervisor::BatterySupervisorData& _devices;
    const uint8_t _noResponseMaxCount;

    CommonTypes::DeviceCategory category() const;
    void onConnect(const DeviceId& device);
    void handleResponse(const DeviceId& device);
    void handleNoResponse(const DeviceId& device);
    void handleWrongRespondent(const DeviceId& device);
    bool connected(const DeviceId& device) const;
    bool pollEnabled(const DeviceId& device);
    uint8_t deviceCount(uint8_t group) const;
    uint8_t groupCount() const;
    void onDisconnect(uint8_t address);
};

}
}
}
