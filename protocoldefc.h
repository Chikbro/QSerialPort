#ifndef PROTOCOLDEFC_H
#define PROTOCOLDEFC_H
#include <QByteArray>
namespace SEDP
{
#define CRC_SIZE         2
#define MIN_PACKET_SIZE  10 // 2feed+6header+2crc
#define FEED1            0xAA
#define FEED2            0x55

  enum DeviceType
  {
    DeviceType_BATTERY    = 0x04  // battarey supervisor
  };

  enum Command
  {
    Command_GetPassport          = 0x00,
    Command_SetPassport          = 0x01,
    Command_GetInfo              = 0x02,
    Command_SetInfo              = 0x03,
    Command_GetOpData            = 0x04,
    Command_SetOpData            = 0x05,
    Command_GetConfig            = 0x06,
    Command_SetConfig            = 0x07,
    Command_NotSupport           = 0x08
  };


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

  enum StateExchange
  {
    StateExchange_WAIT_FEED,
    StateExchange_RECEIVE_HEAD,
    StateExchange_RECEIVE_BODY,
    StateExchange_PACKET_RECEIVED
  };

  enum AnswerCode
  {
    AnswerCode_Ok                  = 0,
    AnswerCode_CommandNotSupported = 1,
    AnswerCode_PackageFormingError = 2
  };
  /* Экспортируемые функции --------------------------------------------------- */

  //uint16_t getCRC(const uint8_t* data, size_t len);  // Вычисление CRC пакета данных



}  // namespace Protocol

#endif // PROTOCOLDEFC_H
