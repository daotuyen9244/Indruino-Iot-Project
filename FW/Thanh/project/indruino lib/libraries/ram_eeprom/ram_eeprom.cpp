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

void RamEeprom::resetRam()
{
    if (p_ram == &ram)
        return;
    p_ram = &ram;
}

template <class T>
bool RamEeprom::write2RomAll(int addRom, int addRam, const T &value, SRAM *p_ram_arr)
{
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom > _SIZE_OF_EEPROM)
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
    if(len >= p_rom->sizeRom) return 0;
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom > _SIZE_OF_EEPROM)
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
    if (addRom < 0 || addRom > _SIZE_OF_EEPROM)
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
    if(len>p_ram->sizeRam) return 0;
    uint16_t size = p_ram_arr->sizeRam;
    if ((addRam < 0) || (addRam > size))
        return 0;
    if (addRom < 0 || addRom > _SIZE_OF_EEPROM)
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

bool RamEeprom::write2RomChar(int addRom, int addRam, SRAM *p_ram_arr)
{
    int8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomChar(int addRom, int addRam)
{
    int8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomUChar(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomUChar(int addRom, int addRam)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomUShort(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint16_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomUShort(int addRom, int addRam)
{
    uint16_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomInt(int addRom, int addRam, SRAM *p_ram_arr)
{
    int32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomInt(int addRom, int addRam)
{
    int32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomUInt(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomUInt(int addRom, int addRam)
{
    uint32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomLong(int addRom, int addRam, SRAM *p_ram_arr)
{
    int32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomLong(int addRom, int addRam)
{
    int32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomULong(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomULong(int addRom, int addRam)
{
    uint32_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomLong64(int addRom, int addRam, SRAM *p_ram_arr)
{
    int64_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomLong64(int addRom, int addRam)
{
    int64_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomULong64(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint64_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomULong64(int addRom, int addRam)
{
    uint64_t temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomFloat(int addRom, int addRam, SRAM *p_ram_arr)
{
    float temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomFloat(int addRom, int addRam)
{
    float temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomDouble(int addRom, int addRam, SRAM *p_ram_arr)
{
    double temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomDouble(int addRom, int addRam)
{
    double temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomBool(int addRom, int addRam, SRAM *p_ram_arr)
{
    bool temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RomBool(int addRom, int addRam)
{
    bool temp = 0;
    return write2RomAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RomString(int addRom, int addRam, int len, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, len, temp, p_ram_arr);
}
bool RamEeprom::write2RomString(int addRom, int addRam, int len)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, len, temp, p_ram);
}
bool RamEeprom::write2RomBytes(int addRom, int addRam, int len, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, len, temp, p_ram_arr);
}
bool RamEeprom::write2RomBytes(int addRom, int addRam, int len)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, len, temp, p_ram);
}
//write2rom

//write2ram
bool RamEeprom::write2RamByte(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamByte(int addRom, int addRam)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamShort(int addRom, int addRam, SRAM *p_ram_arr)
{
    int16_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamShort(int addRom, int addRam)
{
    int16_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamChar(int addRom, int addRam, SRAM *p_ram_arr)
{
    int8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamChar(int addRom, int addRam)
{
    int8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamUChar(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamUChar(int addRom, int addRam)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamUShort(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint16_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamUShort(int addRom, int addRam)
{
    uint16_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamInt(int addRom, int addRam, SRAM *p_ram_arr)
{
    int32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamInt(int addRom, int addRam)
{
    int32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamUInt(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamUInt(int addRom, int addRam)
{
    uint32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamLong(int addRom, int addRam, SRAM *p_ram_arr)
{
    int32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamLong(int addRom, int addRam)
{
    int32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamULong(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamULong(int addRom, int addRam)
{
    uint32_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamLong64(int addRom, int addRam, SRAM *p_ram_arr)
{
    int64_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamLong64(int addRom, int addRam)
{
    int64_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamULong64(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint64_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamULong64(int addRom, int addRam)
{
    uint64_t temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamFloat(int addRom, int addRam, SRAM *p_ram_arr)
{
    float temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamFloat(int addRom, int addRam)
{
    float temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamDouble(int addRom, int addRam, SRAM *p_ram_arr)
{
    double temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamDouble(int addRom, int addRam)
{
    double temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamBool(int addRom, int addRam, SRAM *p_ram_arr)
{
    bool temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram_arr);
}
bool RamEeprom::write2RamBool(int addRom, int addRam)
{
    bool temp = 0;
    return write2RamAll(addRom, addRam, temp, p_ram);
}
bool RamEeprom::write2RamString(int addRom, int addRam, int len, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, len, temp, p_ram_arr);
}
bool RamEeprom::write2RamString(int addRom, int addRam, int len)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, len, temp, p_ram);
}
bool RamEeprom::write2RamBytes(int addRom, int addRam, int len, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, len, temp, p_ram_arr);
}
bool RamEeprom::write2RamBytes(int addRom, int addRam, int len)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, len, temp, p_ram);
}

//write2ram

//function
bool RamEeprom::loadRam2Rom(int addRom, int addRam, int lenRam, SRAM *p_ram_arr)
{
    if(lenRam >= p_ram->sizeRam) return false;
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, lenRam,temp, p_ram_arr);
}
bool RamEeprom::loadRam2Rom(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, p_ram_arr->sizeRam,temp, p_ram);
}
bool RamEeprom::loadRam2Rom(int addRom, int addRam, int lenRam)
{   
    if(lenRam >=p_ram->sizeRam) return false;
    uint8_t temp = 0;
    return write2RomAll(addRom, addRam, lenRam, temp, p_ram);
}

bool RamEeprom::loadRom2Ram(int addRom, int addRam, int lenRom, SRAM *p_ram_arr)
{
    if(lenRom >=p_rom->sizeRom) return false;
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, lenRom,temp, p_ram_arr);
}
bool RamEeprom::loadRom2Ram(int addRom, int addRam, SRAM *p_ram_arr)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, p_rom->sizeRom, p_ram_arr);
}
bool RamEeprom::loadRom2Ram(int addRom, int addRam, int lenRom)
{
    uint8_t temp = 0;
    return write2RamAll(addRom, addRam, lenRom, temp,p_ram);
}
//function
RamEeprom synData;
