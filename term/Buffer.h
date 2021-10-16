#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <DeviceCategory.h>
#include <QtSerialPort/QSerialPortInfo>
#include <Command.h>
#include <port.h>
#include <QThread>
#define TIMEOUT 300;
typedef uint8_t BUFF[9];
namespace SEDP{
enum Position
{
    Position_FEED1       = 0x00,
    Position_FEED2       = 0x01,
    Position_ADDR        = 0x02,
    Position_TYPE        = 0x03,
    Position_SIZE_L      = 0x04,
    Position_SIZE_H      = 0x05,
    Position_CMD         = 0x06,
    Position_RESERVED    = 0x07,
    Position_BODY        = 0x08
};

#define CRC_SIZE 2;
#define Packet_size 10;

class Buffer
{
private:
    static bool CheckCRC();
    static bool WriteHeader(InternalMonitoring::Command cmd);
    static uint8_t getPosition()
{
    return _addres;
}
    static bool framingPacket();
    uint8_t clear()
    {
        return 0;
    }
    static void sendPacket();
    QThread *thread=new QThread;
    static uint8_t _addres;
    static const  CommonTypes::DeviceCategory _thisType;
    static const uint8_t _feed1;
    static const uint8_t _feed2;
    static const uint8_t _crcSize =  CRC_SIZE;
    static const uint8_t _minPacketSize = Packet_size;
    static size_t _packetSize;
    static Buffer _buffer;
    static Port COM_First;
    static Port COM_Second;
};
}
#endif
