#include "Supervisordevice.h"

namespace InternalMonitoring {
namespace BatterySupervisor {

SupervisorDevice::SupervisorDevice(Dispatcher& dispatcher, uint8_t noResponseMaxCount, ImmediateCommandProvider& immCmdProvider,
        MonitoredData::BatterySupervisor::BatterySupervisorArray& devices, const Data::DataObject<Settings::SabParams>& params) :
                SlaveDevice(dispatcher, _cmdProvider, immCmdProvider, _cmdFactory),
                _devices(devices),
                _noResponseMaxCount(noResponseMaxCount),
                _params(params)
{	}

CommonTypes::DeviceCategory SupervisorDevice::category() const {
    return CommonTypes::DeviceCategory::BatterySupervisor;
}
void SupervisorDevice::onConnect(const DeviceId& device) {
    if(device.address >= _devices.size()) {
        return;
    }
    _devices[device.address].connected().set(true);
}
void SupervisorDevice::onDisconnect(uint8_t address) {
    if(address >= _devices.size()) {
        return;
    }
    _devices[address].connected().set(false);
}
void SupervisorDevice::handleResponse(const DeviceId& device) {
    if(device.address >= _devices.size()) {
        return;
    }
    _devices[device.address].serviceData().noResponseCount = 0;
}
void SupervisorDevice::handleNoResponse(const DeviceId& device) {
    if(!connected(device)) {
        return;
    }
    if(device.address >= _devices.size()) {
        return;
    }
    auto& noResponseCount = _devices[device.address].serviceData().noResponseCount;
    if(++noResponseCount >= _noResponseMaxCount) {
        noResponseCount = 0;
        onDisconnect(device.address);
    }
}
void SupervisorDevice::handleWrongRespondent(const DeviceId& device) {
    handleResponse(device);
}
bool SupervisorDevice::connected(const DeviceId& device) const {
    if(device.address >= _devices.size()) {
        return false;
    }
    bool connected = false;
    _devices[device.address].connected().copy(connected);
    return connected;
}
bool SupervisorDevice::pollEnabled(const DeviceId& device) {
    Settings::SabParams params;
    if(!_params.copy(params)) {
        return false;
    }
    if(device.address >= params.maxCount) {
        return false;
    }
    return params.pollEnabled[device.address];
}
uint8_t SupervisorDevice::deviceCount(uint8_t group) const {
    return _devices.max_size();
}
uint8_t SupervisorDevice::groupCount() const {
    return 1;
}

}
}
