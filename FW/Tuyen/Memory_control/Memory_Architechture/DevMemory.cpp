#include "DevMemory.h"

void DevMemory::write_ram_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = 0; t < lens; t++)
    {
        *((char *)&MemMap + t) = *(data + t - add);
    }
}
unsigned char DevMemory::read_ram_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = add; t < lens; t++)
    {
        *(data + t - add) = *((char *)&MemMap + t);
    }
}
void DevMemory::write_ram_UChar(uint16_t add, unsigned char data)
{
    MemMap.DevUChar[add] = data;
}
unsigned char DevMemory::read_ram_UChar(uint16_t add)
{

    return MemMap.DevUChar[add];
}

void DevMemory::write_ram_Char(uint16_t add, char data)
{
    MemMap.DevChar[add] = data;
}
char DevMemory::read_ram_Char(uint16_t add)
{
    return MemMap.DevChar[add];
}

void DevMemory::write_ram_UInt(uint16_t add, unsigned int data)
{
    MemMap.DevUInt[add] = data;
}
unsigned int DevMemory::read_ram_UInt(uint16_t add)
{
    return MemMap.DevUInt[add];
}

void DevMemory::write_ram_Int(uint16_t add, int data)
{
    MemMap.DevInt[add] = data;
}
int DevMemory::read_ram_Int(uint16_t add)
{
    return MemMap.DevInt[add];
}

void DevMemory::write_ram_UInt32(uint16_t add, unsigned long data)
{
    MemMap.DevUInt32[add] = data;
}
unsigned long DevMemory::read_ram_UInt32(uint16_t add)
{
    return MemMap.DevUInt32[add];
}

void DevMemory::write_ram_Int32(uint16_t add, long data)
{
    MemMap.DevInt32[add] = data;
}
long DevMemory::read_ram_Int32(uint16_t add)
{
    return MemMap.DevInt32[add];
}

void DevMemory::write_ram_Float(uint16_t add, float data)
{
    MemMap.DevFloat[add] = data;
}
float DevMemory::read_ram_Float(uint16_t add)
{
    return MemMap.DevFloat[add];
}

void DevMemory::write_ram_Double(uint16_t add, double data)
{
    MemMap.DevDouble[add] = data;
}
double DevMemory::read_ram_Double(uint16_t add)
{
    return MemMap.DevDouble[add];
}
bool DevMemory::setOutputAdd(uint16_t add, unsigned char lens)
{
    int _temp = ((int)add + (int)lens) - ADD_LENS;
    if (_temp >= 0)
    {
        _maxOut = lens;
        _OutputStart = add;
        return 1;
    }
    else
    {
        return 0;
    }
}
bool DevMemory::setInputAdd(uint16_t add, unsigned char lens)
{
    int _temp = ((int)add + (int)lens) - ADD_LENS;
    if (_temp >= 0)
    {
        _maxIn = lens;
        _InputStart = add;
        return 1;
    }
    else
    {
        return 0;
    }
}
unsigned char DevMemory::InputAddBegin()
{
    return _InputStart;
}
unsigned char DevMemory::OutputAddBegin()
{
    return _OutputStart;
}
unsigned char DevMemory::InputLens()
{
    return _maxIn;
}
unsigned char DevMemory::OutputLens()
{
    return _maxOut;
}
unsigned char DevMemory::ReadInPut(uint16_t add)
{
    return MemMap.DevChar[_InputStart + add];
}
unsigned char DevMemory::ReadOutPut(uint16_t add)
{
    return MemMap.DevChar[_OutputStart + add];
}
bool DevMemory::WriteOutPut(uint16_t add, unsigned char data)
{
    if (add <= _maxOut) // Dem tu 0
    {
        MemMap.DevChar[_OutputStart + add] = data;
        return 1;
    }
    else
    {
        return 0;
    }
}
#ifdef USE_EPPROM
bool DevMemory::initEPPROM()
{
    if (!EEPROM.begin(EEPROM_SIZE))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
unsigned char DevMemory::readEPPROM(uint16_t add)
{
    return EEPROM.read(add);
}

void DevMemory::saveEPPROM()
{
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
bool DevMemory::writeEPPROM(uint16_t add, unsigned char data)
{
    EEPROM.write(add, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
void DevMemory::write_rom_UChar(uint16_t add, unsigned char data)
{
    EEPROM.writeUChar(add, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned char DevMemory::read_rom_UChar(uint16_t add)
{
    return EEPROM.readUChar(add);
}

void DevMemory::write_rom_Char(uint16_t add, char data)
{
    EEPROM.writeChar(add + ECHAR_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
char DevMemory::read_rom_Char(uint16_t add)
{
    return EEPROM.readChar(add + ECHAR_START);
}

void DevMemory::write_rom_UInt(uint16_t add, unsigned int data)
{
    EEPROM.writeUInt(add + EUINT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned int DevMemory::read_rom_UInt(uint16_t add)
{
    return EEPROM.readUInt(add + EUINT_START);
}

void DevMemory::write_rom_Int(uint16_t add, int data)
{
    EEPROM.writeInt(add + EINT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
int DevMemory::read_rom_Int(uint16_t add)
{
    return EEPROM.readInt(add + EINT_START);
}

void DevMemory::write_rom_UInt32(uint16_t add, unsigned long data)
{
    EEPROM.writeULong(add + EUINT32_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned long DevMemory::read_rom_UInt32(uint16_t add)
{
    return EEPROM.readULong(add + EUINT32_START);
}

void DevMemory::write_rom_Int32(uint16_t add, long data)
{
    EEPROM.writeLong(add + EINT32_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
long DevMemory::read_rom_Int32(uint16_t add)
{
    return EEPROM.readLong(add + EINT32_START);
}

void DevMemory::write_rom_Float(uint16_t add, float data)
{
    EEPROM.writeFloat(add + EFLOAT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
float DevMemory::read_rom_Float(uint16_t add)
{
    return EEPROM.readFloat(add + EFLOAT_START);
}

void DevMemory::write_rom_Double(uint16_t add, double data)
{
    EEPROM.writeDouble(add + EDBL_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
double DevMemory::read_rom_Double(uint16_t add)
{
    return EEPROM.readDouble(add + EDBL_START);
}
void DevMemory::copy_rom_to_ram_UChar(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUChar[fadd] = DevMemory::read_rom_UChar(radd);
}
void DevMemory::copy_ram_to_rom_UChar(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UChar(radd, MemMap.DevUChar[fadd]);
}

void DevMemory::copy_rom_to_ram_Char(unsigned char radd, unsigned char fadd)
{
    MemMap.DevChar[fadd] = DevMemory::read_rom_Char(radd);
}
void DevMemory::copy_ram_to_rom_Char(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Char(radd, MemMap.DevChar[fadd]);
}

void DevMemory::copy_rom_to_ram_UInt(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt[radd] = DevMemory::read_rom_UInt(radd);
}
void DevMemory::copy_ram_to_rom_Uint(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt(radd, MemMap.DevUInt[fadd]);
}

void DevMemory::copy_rom_to_ram_Int(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt[radd] = DevMemory::read_rom_Int(radd);
}
void DevMemory::copy_ram_to_rom_int(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Int(radd, MemMap.DevInt[fadd]);
}

void DevMemory::copy_rom_to_ram_UInt32(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_rom_UInt32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Int32(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt32[radd] = DevMemory::read_rom_Int32(radd);
}
void DevMemory::copy_ram_to_rom_Int32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_ULong(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_rom_ULong(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Long(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt32[radd] = DevMemory::read_rom_Int32(radd);
}
void DevMemory::copy_ram_to_rom_Long(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Int32(radd, MemMap.DevInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Float(unsigned char radd, unsigned char fadd)
{
    MemMap.DevFloat[radd] = DevMemory::read_rom_Float(radd);
}
void DevMemory::copy_ram_to_rom_Float(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Float(radd, MemMap.DevFloat[fadd]);
}
void DevMemory::copy_rom_to_ram_Double(unsigned char radd, unsigned char fadd)
{
    MemMap.DevDouble[radd] = DevMemory::read_rom_Double(radd);
}
void DevMemory::copy_ram_to_rom_Double(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Double(radd, MemMap.DevDouble[fadd]);
}
void DevMemory::write_rom_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = add; t < lens; t++)
    {
        EEPROM.write(t, *(data + (t - add)));
    }
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned char DevMemory::read_rom_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = add; t < lens; t++)
    {
        *((char *)data + t - add) = EEPROM.read(t);
    }
}
#ifdef USE_ExI2C
bool DevMemory::initI2CEPPROM()
{
    eeprom.initialize();
    return 1;
}
unsigned char DevMemory::readI2C_rom(uint16_t add)
{
    return eeprom.readByte(add);
}
bool DevMemory::writeI2C_rom(uint16_t add, unsigned char data)
{
    eeprom.writeByte(add, data);
}
void DevMemory::write_I2C_rom_UChar(uint16_t add, unsigned char data)
{
    eeprom.writeByte(add, data);
}
unsigned char DevMemory::read_I2C_rom_UChar(uint16_t add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_Char(uint16_t add, char data)
{
    eeprom.writeByte(add, data);
}
char DevMemory::read_I2C_rom_Char(uint16_t add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_UInt(uint16_t add, unsigned int data)
{
    eeprom.writeBytes(add, 2, (byte *)data);
}
unsigned int DevMemory::read_I2C_rom_UInt(uint16_t add)
{
    uint16_t _x = 0;
    eeprom.readBytes(add, 2, (byte *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int(uint16_t add, int data)
{
    eeprom.writeBytes(add, 2, (byte *)data);
}
int DevMemory::read_I2C_rom_Int(uint16_t add)
{
    int16_t _x = 0;
    eeprom.readBytes(add, 2, (byte *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_UInt32(uint16_t add, unsigned long data)
{
    eeprom.writeBytes(add, 4, (byte *)data);
}
unsigned long DevMemory::read_I2C_rom_UInt32(uint16_t add)
{
    uint32_t _x = 0;
    eeprom.readBytes(add, 4, (byte *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int32(uint16_t add, long data)
{
    eeprom.writeBytes(add, 4, (byte *)data);
}
long DevMemory::read_I2C_rom_Int32(uint16_t add)
{
    int32_t _x = 0;
    eeprom.readBytes(add, 4, (byte *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Float(uint16_t add, float data)
{
    union {
        float a;
        unsigned char bytes[4];
    } thing;
    thing.a = data;
    eeprom.writeBytes(add, 4, (byte *)(thing.bytes));
}
float DevMemory::read_I2C_rom_Float(uint16_t add)
{
    float _x = 0;
    union {
        float a;
        unsigned char bytes[4];
    } thing;

    eeprom.readBytes(add, 4, (byte *)(thing.bytes));
    _x = thing.a;
    return _x;
}

void DevMemory::write_I2C_rom_Double(uint16_t add, double data)
{
    union {
        double a;
        unsigned char bytes[8];
    } thing;
    thing.a = data;
    eeprom.writeBytes(add, 8, (byte *)(thing.bytes));
}
double DevMemory::read_I2C_rom_Double(uint16_t add)
{
    double _x = 0;
    union {
        float a;
        unsigned char bytes[8];
    } thing;

    eeprom.readBytes(add, 8, (byte *)(thing.bytes));
    _x = thing.a;
    return _x;
}
void DevMemory::copy_I2C_rom_to_ram_UChar(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUChar[fadd] = DevMemory::read_I2C_rom_UChar(radd);
}
void DevMemory::copy_ram_to_I2C_rom_UChar(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_UChar(radd, MemMap.DevUChar[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_Char(unsigned char radd, unsigned char fadd)
{
    MemMap.DevChar[fadd] = DevMemory::read_I2C_rom_Char(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Char(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_Char(radd, MemMap.DevChar[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_UInt(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt[radd] = DevMemory::read_I2C_rom_UInt(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Uint(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_UInt(radd, MemMap.DevUInt[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_Int(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt[radd] = DevMemory::read_I2C_rom_Int(radd);
}
void DevMemory::copy_ram_to_I2C_rom_int(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_Int(radd, MemMap.DevInt[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_UInt32(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt32[radd] = DevMemory::read_I2C_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_I2C_rom_UInt32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_Int32(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt32[radd] = DevMemory::read_I2C_rom_Int32(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Int32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_ULong(unsigned char radd, unsigned char fadd)
{
    MemMap.DevUInt32[radd] = DevMemory::read_I2C_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_I2C_rom_ULong(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_Long(unsigned char radd, unsigned char fadd)
{
    MemMap.DevInt32[radd] = DevMemory::read_I2C_rom_Int32(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Long(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_Int32(radd, MemMap.DevInt32[fadd]);
}

void DevMemory::copy_I2C_rom_to_ram_Float(unsigned char radd, unsigned char fadd)
{
    MemMap.DevFloat[radd] = DevMemory::read_I2C_rom_Float(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Float(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_Float(radd, MemMap.DevFloat[fadd]);
}
void DevMemory::copy_I2C_rom_to_ram_Double(unsigned char radd, unsigned char fadd)
{
    MemMap.DevDouble[radd] = DevMemory::read_I2C_rom_Double(radd);
}
void DevMemory::copy_ram_to_I2C_rom_Double(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_I2C_rom_Double(radd, MemMap.DevDouble[fadd]);
}
void DevMemory::write_I2C_rom_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    eeprom.writeBytes(add, lens, data);
}
unsigned char DevMemory::read_I2C_rom_Block(uint16_t add, unsigned int lens, unsigned char *data)
{
    eeprom.readBytes(add, lens, data);
}
#endif
#endif