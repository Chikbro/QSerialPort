#include <cstdint>
#include <mainwindow.h>
#include <QMainWindow>

namespace CommonTypes
{
enum class DeviceCategory : uint8_t
{
    Controller = 0x00,
    Inverter = 0x02,
    BatterySupervisor = 0x04,
    Climatic = 0x10,
    AutomatAc = 0x11,
    AutomatDc = 0x12,
    Bypass = 0x82,
    AutomatDryContact = 0x13
};
}
