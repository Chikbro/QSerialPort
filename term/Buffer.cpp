    #include <Buffer.h>
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

bool::SEDP::Buffer::WriteHeader(InternalMonitoring::Command cmd)
{
    _buffer.clear();
}

bool::SEDP::Buffer::framingPacket()
{
    if (_buffer.getPosition()>=_minPacketSize-_crcSize)
    {
       uint16_t Packet_Size=static_cast<uint16_t>(_buffer.getPosition()+_crcSize);
       _buffer[Position_SIZE_L]=maxByte(Packet_Size);
       _buffer[Position_SIZE_H]=minByte(Packet_Size);
       _buffer[Position_ADDR]=_addres;
    }
}

void::SEDP::Buffer::sendPacket()
{//отправка пакета!!!
  //  connect(thread,SIGNAL(started()) worker, SLOT(process()));
    COM_First.children();
    COM_Second.parent();
    COM_First.ConnectPort();
    COM_Second.ConnectPort();
    COM_First.blockSignals(true);
}
