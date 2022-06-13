#include <Buffer.h>
#include <Command.h>
#include <QThread>
#include<QtSerialPort>
#include <QIODevice>
#include <port.h>
#include <QDebug>

bool Protocol::CheckCRC()
{
    if (_crcSize>0)
    {
        return true;
    }
    else
    {
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
     //if (_buffer.getPosition()>=Packet_Size-_crcSize)
    {
//      uint16_t Packet_Size=static_cast<uint16_t>(_buffer.getPosition()+_crcSize);
//      Protocol::_buffer[Position::SIZE_L]=maxByte(Packet_Size);
//      _buffer[Position::SIZE_H]=minByte(Packet_Size);
//      _buffer[Position::ADDR]=_addres;
    }
    return true;
}

bool Protocol::write_to_port(QByteArray _data)
{
    if (_port.thisPort.isOpen())
    {
        _port.thisPort.write(_data);
        return _port.thisPort.waitForBytesWritten(300);
    }
        else return false;
}

QByteArray Protocol::read()
{
    QByteArray _data;
    while (_port.thisPort.waitForReadyRead(300))
    {
        _data=_port.thisPort.readAll();
    }
    _port.outPort(_data);
    return _data;
}

void Protocol::write(QByteArray _request)
{
    bool Ok=write_to_port(_request);
    QByteArray read_data=read();
    if (!(read_data.isNull())||Ok)
       _port.outPort("Сообщение прошло:"+read_data);
    else _port.outPort("Не прошла отрпавка");
}

void Protocol::createBuf()
{
    buf.resize(9);
    buf[0]=0xaa;
    buf[1]=0x55;
    buf[2]=0x00;
    buf[3]=0x04;
    buf[4]=0x02;
    buf[5]=0x00;
    buf[6]=0x00;
    buf[7]=0x00;
    buf[8]=0x00;
    buf.toHex();
    qDebug()<<buf;
}
