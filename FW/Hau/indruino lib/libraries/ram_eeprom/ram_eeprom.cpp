#include "ram_eeprom.h"

void RamEeprom::init()
{
    if (p_ram == nullptr)
        p_ram = &ram;
    if (p_rom == nullptr)
        p_rom = &rom;
    // Serial.println("khoi tao");
}

RamEeprom::RamEeprom()
{
}
RamEeprom::~RamEeprom()
{
}

void RamEeprom::setRam(SRAM &p_ram_arr)
{
    if (p_ram == &p_ram_arr)
        return;
    p_ram = &p_ram_arr;
}

void RamEeprom::resetRam() {
    if(p_ram == &ram)
        return;
    p_ram = &ram;    
}

template <class T>
bool RamEeprom::write2RomAll(int addRom, int addRam, const T &value, SRAM *p_ram_arr)
{
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
        return 0;

    for (uint16_t count = 0; count < sizeof(T); count++)
    {
        uint8_t temp = p_ram_arr->readByte(addRam + count);
        // Serial.println(temp, HEX);
        EEPROM.write(addRom + count, temp);    
    }
#ifdef ESP32 || ESP8266
    return EEPROM.commit();
#else
    return true;
#endif
}

template <class T>
bool RamEeprom::write2RomAll(int addRom, int addRam, uint16_t len, const T &value, SRAM *p_ram_arr)
{
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
        return 0;

    for (uint16_t count = 0; count < len; count++)
    {
        uint8_t temp = p_ram_arr->readByte(addRam + count);
        // Serial.println(temp, HEX);
        EEPROM.write(addRom + count, temp);
    }
#ifdef ESP32 || ESP8266
    return EEPROM.commit();
#else
    return true;
#endif
}

// template <class T>
// bool RamEeprom::write2RomAll(int addRom, int addRam, const T &value)
// {
//     uint16_t size = p_ram->sizeRam;
//     if ((addRam < 0) || (addRam > size))
//         return 0;
//     if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
//         return 0;

//     for (uint16_t count = 0; count < sizeof(T); count++)
//     {
//         uint8_t temp = p_ram->readByte(addRam + count);
//         // Serial.println(temp, HEX);
//         EEPROM.writeByte(addRom + count, temp);
//     }
// #ifdef ESP32 || ESP8266
//     return EEPROM.commit();
// #else
//     return true;
// #endif
// }

// template <class T>
// bool RamEeprom::write2RomAll(int addRom, int addRam, uint16_t len, const T &value)
// {
//     uint16_t size = p_ram->sizeRam;
//     if ((addRam < 0) || (addRam > size))
//         return 0;
//     if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
//         return 0;

//     for (uint16_t count = 0; count < len; count++)
//     {
//         uint8_t temp = p_ram->readByte(addRam + count);
//         // Serial.println(temp, HEX);
//         EEPROM.writeByte(addRom + count, temp);
//     }
// #ifdef ESP32 || ESP8266
//     return EEPROM.commit();
// #else
//     return true;
// #endif
// }

template <class T>
bool RamEeprom::write2RamAll(int addRom, int addRam, const T &value, SRAM *p_ram_arr)
{
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
        return 0;

    for (uint16_t count = 0; count < sizeof(T); count++)
    {
        uint8_t temp = EEPROM.read(addRom + count);
        // Serial.println(temp, HEX);
        p_ram_arr->writeByte(addRam + count, temp);
    }
    return true;
}

template <class T>
bool RamEeprom::write2RamAll(int addRom, int addRam, uint16_t len, const T &value, SRAM *p_ram_arr)
{
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom >= _SIZE_OF_EEPROM)
        return 0;

    for (uint16_t count = 0; count < len; count++)
    {
        uint8_t temp = EEPROM.read(addRom + count);
        // Serial.println(temp, HEX);
        p_ram_arr->writeByte(addRam + count, temp);
    }
    return true;
}
//write2rom
bool RamEeprom::write2RomByte(int addRom, int addRam)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomByte(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomShort(int addRom, int addRam)
{
    int16_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomShort(int addRom, int addRam, SRAM *p_ram_arr)
{
    int16_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
//write2rom


//write2ram
bool RamEeprom::write2RamByte(int addRom, int addRam, SRAM *p_ram_arr) {
    uint8_t temp =0;
    return write2RamAll(addRom, addRam, temp,p_ram_arr);
}
bool RamEeprom::write2RamByte(int addRom, int addRam)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}

bool RamEeprom::write2RamShort(int addRom, int addRam, SRAM *p_ram_arr)
{
    int16_t temp=0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}

bool RamEeprom::write2RamShort(int addRom, int addRam)
{
    int16_t temp =0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}

//write2ram

