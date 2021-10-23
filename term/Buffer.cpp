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
    _buffer.clear();//для отладки начинать с 0
    return true;
}

bool::SEDP::Buffer::framingPacket()
{
    if (_buffer.getPosition()>=_minPacketSize-_crcSize)
    {
       uint16_t Packet_Size=static_cast<uint16_t>(_buffer.getPosition()+_crcSize);
       //_buffer[Position::SIZE_L]=maxByte(Packet_Size);
      // _buffer[Position::SIZE_H]=minByte(Packet_Size);
      // _buffer[Position::ADDR]=_addres;
    }
    return true;
}

void::SEDP::Buffer::sendPacket()
{//отправка пакета!!!
    //connect(COM_First,SIGNAL(started()), this, SLOT(process()));

}
