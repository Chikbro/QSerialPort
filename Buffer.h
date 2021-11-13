#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <DeviceCategory.h>
#include <QtSerialPort/QSerialPortInfo>
#include <Command.h>
#include <port.h>
#include <QThread>

#define TIMEOUT 300;
#define CRC_SIZE 2;
#define PACKET_SIZE 10;

typedef uint8_t BUFF[9];
namespace SEDP{
enum class Position: uint8_t
{
    FEED1       = 0x00,
    FEED2       = 0x01,
    ADDR        = 0x02,
    TYPE        = 0x03,
    SIZE_L      = 0x04,
    SIZE_H      = 0x05,
    CMD         = 0x06,
    RESERVED    = 0x07,
    BODY        = 0x08
};

class Buffer
{
public:
private:
    static bool CheckCRC();
    static bool WriteHeader();
    int getPosition()
{
    return _addres;
}
    static bool framingPacket();
    uint8_t clear()
    {
        return 0;
    }
    bool sendPacket();
    QThread *thread=new QThread;
    uint8_t _addres;
    static const  CommonTypes::DeviceCategory _thisType;
    static const uint8_t _feed1;
    static const uint8_t _feed2;
    static const uint8_t _crcSize = CRC_SIZE;
    static const uint8_t _minPacketSize = PACKET_SIZE;
    static size_t _packetSize;
    static Buffer _buffer;
    QSerialPort thisPort;
    static size_t Packet_Size;
    static const uint8_t minByte= _minPacketSize;
    static const uint8_t maxByte;
};
}
#endif
