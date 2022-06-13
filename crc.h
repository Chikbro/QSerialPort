#include <QCoreApplication>
#include <cstdint>
#include <QDebug>
class Crc16Ccitt {
private:
        const uint16_t _additionalValue;
        const uint16_t _initialValue;
        uint8_t _crcl;
        uint8_t _crch;
public:
        Crc16Ccitt(uint16_t initialValue, uint16_t additionalValue = 0) :
            _additionalValue(additionalValue),
            _initialValue(initialValue)
    {
            reset();
    }

        void process(const uint8_t* data, size_t len){
            for(size_t cnt = 0; cnt < len; ++cnt) {
                    uint8_t tmp = data[cnt] ^ _crcl;
                    tmp ^= (tmp << 4);
                    _crcl = _crch;
                    _crch = tmp ^ ((tmp >> 5) & 0x07);
                    _crcl ^= (tmp << 3);
                    _crcl ^= ((tmp >> 4) & 0x0F);
            }
    }
        void reset(){
            _crch = _initialValue & uint16_t(0xFF00) / uint16_t(1 << 8);
            _crcl = _initialValue & uint8_t(0xFF);
    }
        uint16_t value() const {
            return ((uint16_t(_crch) << 8) | _crcl) + _additionalValue;
        }
};
