#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <port.h>
#include <DeviceCategory.h>
#include <CommandID.h>
#include <PassportDevice.h>
#include <mainwindow.h>

#define TIMEOUT 300;
//#define CRC_SIZE 2;
#define PACKET_SIZE 10;

typedef uint8_t BUFF[9];

//enum class Position: uint8_t
//{
//    FEED1       = 0xAA,
//    FEED2       = 0x55,//
//    ADDR        = 0x00,
//    TYPE        = 0x04,//SUPERVISOR
//    SIZE_L      = 0x02,
//    SIZE_H      = 0x00,
//    CMD         = 0x00,
//    RESERVED    = 0x00,//COMAND 0
//    BODY        = 0x00//GROUP 0
//};

class Protocol
{
public:
    Protocol(Port& port) :_port( port){}
public slots:
    QByteArray read();
    void write(QByteArray buf);
    bool write_to_port(QByteArray _data);
signals:
    void outport(QByteArray _data);
private:
    Port& _port;
    static bool CheckCRC();
    static bool WriteHeader(uint8_t _buffer);
        size_t getPosition()
    {
    return _addres;
    }
    static bool framingPacket(uint8_t _buffer);
    uint8_t clear()
    {
        buf=0;
        return 0;
    }
    uint8_t _addres;
    //static const CommonTypes::DeviceCategory _thisType;
   // static constexpr uint8_t _feed1 { 0x00 };
   // static const uint8_t _feed2;
    static const uint8_t _crcSize = CRC_SIZE;
    static const uint8_t _minPacketSize = PACKET_SIZE;
    static size_t _packetSize;
    static uint8_t _buffer;
    static size_t Packet_Size;
    static const uint8_t minByte = _minPacketSize;
    static const uint8_t maxByte;
public:
    QByteArray buf;
    void createBuf();
};//вместо _data буффер из 9 элементов

#endif
