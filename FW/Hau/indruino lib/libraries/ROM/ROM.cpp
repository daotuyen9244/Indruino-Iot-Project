#include "ROM.h"

template <class T>
T ROM::readAll(int add, T *des)
{
    if (add >= _SIZE_OF_EEPROM || add < 0)
        return 0;

    uint8_t *temp = (uint8_t *)calloc(sizeof(T), sizeof(uint8_t));
    for (uint8_t count = 0; count < sizeof(T); count++)
    {
        uint8_t _value_temp = EEPROM.read(add + count);
        memcpy(temp + count, &_value_temp, sizeof(uint8_t));
    }

    des = (T *)temp;
    return *des;
}
template <class T>
bool ROM::readAll(int add, uint8_t *des, size_t len) //uint8_t data array
{
    if (add >= _SIZE_OF_EEPROM || add < 0)
        return 0;
    //uint8_t *temp = (uint8_t *)calloc(sizeof(T), sizeof(uint8_t));
    for (uint8_t count = 0; count < len; count++)
    {
        uint8_t _value_temp = EEPROM.read(add + count);
        memcpy(des + count, _value_temp, sizeof(uint8_t));
    }
    return true;
}

template <class T>
bool ROM::writeAll(int add, T *value)
{
    if ((add < 0) || (add >= sizeRom))
        return false;
    uint8_t *temp = (uint8_t *)value;
    for (uint8_t count = 0; count < sizeof(T); count++)
    {
        EEPROM.write(add + count, *(temp + count));
    }

    return true;
} //write data at add with len and write it to *p
template <class T>
bool ROM::writeAll(int add, uint8_t *ptr_value, size_t len)
{
    if ((add < 0) || (add >= sizeRom))
        return false;
    for (uint8_t count = 0; count < len; count++)
    {
        EEPROM.write(add + count, *(ptr_value + count));
    }
    return true;
}

//init this ROM
void ROM::init()
{
    if (sizeRom != 0)
        return;
#ifdef ESP32 || ESP8266
    EEPROM.begin(_SIZE_OF_EEPROM);
#endif
    sizeRom = _SIZE_OF_EEPROM;
}
//init this ROM

void ROM::init(int size)
{
    if (sizeRom != 0)
        return;
#ifdef ESP32 || ESP8266
    EEPROM.begin(size);
#endif
    sizeRom = size;
}

//read===================

//readByte this ROM
uint8_t ROM::readByte(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readByte(address);
#else
    uint8_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readByte this ROM
//readShort this ROM
int16_t ROM::readShort(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readShort(address);
#else
    int16_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readShort this ROM

//read===================

//write==================

//writeByte this ROM
bool ROM::writeByte(int address, uint8_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeByte(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeByte this ROM

//writeShort this ROM
bool ROM::writeShort(int address, int16_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeShort(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeShort this ROM

//write===================

uint16_t ROM::getSize(uint16_t size)
{
    return sizeRom;
}

ROM::ROM()
{
}
ROM::~ROM()
{
}

ROM rom;
