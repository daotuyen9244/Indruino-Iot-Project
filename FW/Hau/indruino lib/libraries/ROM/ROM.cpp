#include "ROM.h"

//init this ROM
void ROM::init()
{
    if(sizeRom != 0) return;
    EEPROM.begin(_SIZE_OF_EEPROM);
    sizeRom = _SIZE_OF_EEPROM;
}
//init this ROM

//read===================

//readByte this ROM
uint8_t ROM::readByte(int address)
{
    return EEPROM.readByte(address);
}
//readByte this ROM
//readShort this ROM
int16_t ROM::readShort(int address)
{
    return EEPROM.readShort(address);
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
    return EEPROM.writeByte(address, value);
#endif
}
//writeByte this ROM



//write===================

uint16_t ROM::getSize(uint16_t size) {
    return sizeRom;
}


ROM::ROM()
{
}
ROM::~ROM()
{

}


ROM rom;











