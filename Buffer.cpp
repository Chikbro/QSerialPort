#include <Buffer.h>
#include <Command.h>
#include <QThread>
#include<QtSerialPort>
#include <QIODevice>
#include <port.h>


bool Protocol::CheckCRC()
{
    if (_crcSize>0)
    {
        return true;
    }
    else {
        return false;
    }
}

bool Protocol::WriteHeader(uint8_t _buffer)
{
    _buffer=0;//обнуление буффера
    return true;
}

bool Protocol::framingPacket(uint8_t _buffer)
{
   // if (_buffer.getPosition()>=Packet_Size-_crcSize)
    {
//      uint16_t Packet_Size=static_cast<uint16_t>(_buffer.getPosition()+_crcSize);
//      Protocol::_buffer[Position::SIZE_L]=maxByte(Packet_Size);
//      _buffer[Position::SIZE_H]=minByte(Packet_Size);
//      _buffer[Position::ADDR]=_addres;
    }
    return true;
}

bool Protocol::write_to_port(QByteArray buf)
{
    if (_port.thisPort.isOpen())
    {
        _port.thisPort.write(buf);
        return _port.thisPort.waitForBytesWritten(300);
    }
        else return false;
}

QByteArray Protocol::read()
{
    while (_port.thisPort.waitForReadyRead(300))
    {
        buf=_port.thisPort.readAll();
    }
    _port.outPort(buf);
    return buf;
}

void Protocol::write(QByteArray _request)
{
    bool Ok=write_to_port(_request);
    QByteArray read_data=read();
    if (!(read_data.isNull())||Ok)
        _port.outPort("Сообщение прошло:"+(QString)read_data);
    else _port.outPort("Не прошла отрпавка");
}
