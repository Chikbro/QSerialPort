#include <Buffer.h>
#include <Command.h>
#include <QThread>

bool::SEDP::Buffer::CheckCRC()
{
    if (_crcSize>0)
    {
        return true;
    }
    else {
        return false;
    }
}

bool::SEDP::Buffer::WriteHeader()
{
    _buffer.clear();//обнуление буффера
    return true;
}

bool::SEDP::Buffer::framingPacket()
{
    if (_buffer.getPosition()>=_minPacketSize-_crcSize)
    {
        uint16_t Packet_Size=static_cast<uint16_t>(_buffer.getPosition()+_crcSize);
        _buffer[SEDP::Position::SIZE_L]=SEDP::Buffer::maxByte(Packet_Size);
        _buffer[SEDP::Position::SIZE_H]=SEDP::Buffer::minByte(Packet_Size);
        _buffer[SEDP::Position::ADDR]=_addres;
    }
    return true;
}

void::SEDP::Buffer::sendPacket()
{//отправка пакета!!!
    //connect(COM_First,SIGNAL(started()), this, SLOT(process()));
}
