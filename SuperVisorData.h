#ifndef MONITOREDDEVICEDATA_BATTERYSUPERVISOR_SUPERVISORDATA_HPP_
#define MONITOREDDEVICEDATA_BATTERYSUPERVISOR_SUPERVISORDATA_HPP_
#include <ServiceData.h>
#include <Params.h>
namespace MonitoredData {
namespace BatterySupervisor {

using namespace InternalMonitoring::BatterySupervisor;

class BatterySupervisorData {
public:
    static void init() {
    }
    DataObject<CommonTypes::DevicePassport>& passport() {
        return _passport;
    }
    DataObject<DebugMonitoring::Data::Params>& params() {
        return _params;
    }
    DataObject<bool>& connected() {
        return _connected;
    }
    const DataObject<bool>& connected() const {
        return _connected;d
    }
    Status  & status() {
        return _status;
    }
    const Status& status() const {
        return _status;
    }
    ServiceData& serviceData() {
        return _serviceData;
    }
private:
    ServiceData _serviceData{};
    ValueDataObject<bool> _connected;
};

}
}
#endif /* MONITOREDDEVICEDATA_BATTERYSUPERVISOR_SUPERVISORDATA_HPP_ */
