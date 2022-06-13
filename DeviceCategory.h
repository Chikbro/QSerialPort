#pragma once
#include <cstdint>
#include <mainwindow.h>
#include <QMainWindow>
#include <QByteArray>

namespace CommonTypes
{
enum class DeviceCategory : uint8_t
//class deviceCat
{
//public:
//   QByteArray Controller=0x00;
//   QByteArray Inverter=0x02;
//   QByteArray BatterySupervisor = 0x04;
//   QByteArray Climatic = 0x10;
//   QByteArray AutomatAc = 0x11;
//   QByteArray AutomatDc = 0x12;
//   QByteArray  Bypass = 0x82;
//   QByteArray AutomatDryContact = 0x13;
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
