#include "DevMemory.h"

void DevMemory::write_ram_UChar(byte add, unsigned char data)
{
    DevUChar[add] = data;
}
unsigned char DevMemory::read_ram_UChar(byte add)
{

    return DevUChar[add];
}

void DevMemory::write_ram_Char(unsigned char add, char data)
{
    DevChar[add] = data;
}
char DevMemory::read_ram_Char(unsigned char add)
{
    return DevChar[add];
}

void DevMemory::write_ram_UInt(unsigned char add, unsigned int data)
{
    DevUInt[add] = data;
}
unsigned int DevMemory::read_ram_UInt(unsigned char add)
{
    return DevUInt[add];
}

void DevMemory::write_ram_Int(unsigned char add, int data)
{
    DevInt[add] = data;
}
int DevMemory::read_ram_Int(unsigned char add)
{
    return DevInt[add];
}

void DevMemory::write_ram_UInt32(unsigned char add, unsigned long data)
{
    DevUInt32[add] = data;
}
unsigned long DevMemory::read_ram_UInt32(unsigned char add)
{
    return DevUInt32[add];
}

void DevMemory::write_ram_Int32(unsigned char add, long data)
{
    DevInt32[add] = data;
}
long DevMemory::read_ram_Int32(unsigned char add)
{
    return DevInt32[add];
}

void DevMemory::write_ram_Float(unsigned char add, float data)
{
    DevFloat[add] = data;
}
float DevMemory::read_ram_Float(unsigned char add)
{
    return DevFloat[add];
}

void DevMemory::write_ram_Double(unsigned char add, double data)
{
    DevDouble[add] = data;
}
double DevMemory::read_ram_Double(unsigned char add)
{
    return DevDouble[add];
}
bool DevMemory::setOutputAdd(unsigned char add, unsigned char lens)
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
bool DevMemory::setInputAdd(unsigned char add, unsigned char lens)
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
unsigned char DevMemory::ReadInPut(unsigned char add)
{
    return DevChar[_InputStart + add];
}
unsigned char DevMemory::ReadOutPut(unsigned char add)
{
    return DevChar[_OutputStart + add];
}
bool DevMemory::WriteOutPut(unsigned char add, unsigned char data)
{
    if (add <= _maxOut) // Dem tu 0
    {
        DevChar[_OutputStart + add] = data;
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
unsigned char DevMemory::readEPPROM(unsigned char add)
{
    return EEPROM.read(add);
}

void DevMemory::saveEPPROM()
{
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
bool DevMemory::writeEPPROM(unsigned char add, unsigned char data)
{
    EEPROM.write(add, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
void DevMemory::write_rom_UChar(byte add, unsigned char data)
{
    EEPROM.writeUChar(add, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned char DevMemory::read_rom_UChar(byte add)
{
    return EEPROM.readUChar(add);
}

void DevMemory::write_rom_Char(unsigned char add, char data)
{
    EEPROM.writeChar(add + ECHAR_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
char DevMemory::read_rom_Char(unsigned char add)
{
    return EEPROM.readChar(add + ECHAR_START);
}

void DevMemory::write_rom_UInt(unsigned char add, unsigned int data)
{
    EEPROM.writeUInt(add + EUINT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned int DevMemory::read_rom_UInt(unsigned char add)
{
    return EEPROM.readUInt(add + EUINT_START);
}

void DevMemory::write_rom_Int(unsigned char add, int data)
{
    EEPROM.writeInt(add + EINT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
int DevMemory::read_rom_Int(unsigned char add)
{
    return EEPROM.readInt(add + EINT_START);
}

void DevMemory::write_rom_UInt32(unsigned char add, unsigned long data)
{
    EEPROM.writeULong(add + EUINT32_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned long DevMemory::read_rom_UInt32(unsigned char add)
{
    return EEPROM.readULong(add + EUINT32_START);
}

void DevMemory::write_rom_Int32(unsigned char add, long data)
{
    EEPROM.writeLong(add + EINT32_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
long DevMemory::read_rom_Int32(unsigned char add)
{
    return EEPROM.readLong(add + EINT32_START);
}

void DevMemory::write_rom_Float(unsigned char add, float data)
{
    EEPROM.writeFloat(add + EFLOAT_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
float DevMemory::read_rom_Float(unsigned char add)
{
    return EEPROM.readFloat(add + EFLOAT_START);
}

void DevMemory::write_rom_Double(unsigned char add, double data)
{
    EEPROM.writeDouble(add + EDBL_START, data);
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
double DevMemory::read_rom_Double(unsigned char add)
{
    return EEPROM.readDouble(add + EDBL_START);
}
void DevMemory::copy_rom_to_ram_UChar(unsigned char radd, unsigned char fadd)
{
    DevUChar[fadd] = DevMemory::read_rom_UChar(radd);
}
void DevMemory::copy_ram_to_rom_UChar(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UChar(radd, DevUChar[fadd]);
}

void DevMemory::copy_rom_to_ram_Char(unsigned char radd, unsigned char fadd)
{
    DevChar[fadd] = DevMemory::read_rom_Char(radd);
}
void DevMemory::copy_ram_to_rom_Char(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Char(radd, DevChar[fadd]);
}

void DevMemory::copy_rom_to_ram_UInt(unsigned char radd, unsigned char fadd)
{
    DevUInt[radd] = DevMemory::read_rom_UInt(radd);
}
void DevMemory::copy_ram_to_rom_Uint(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt(radd, DevUInt[fadd]);
}

void DevMemory::copy_rom_to_ram_Int(unsigned char radd, unsigned char fadd)
{
    DevInt[radd] = DevMemory::read_rom_Int(radd);
}
void DevMemory::copy_ram_to_rom_int(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Int(radd, DevInt[fadd]);
}

void DevMemory::copy_rom_to_ram_UInt32(unsigned char radd, unsigned char fadd)
{
    DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_rom_UInt32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Int32(unsigned char radd, unsigned char fadd)
{
    DevInt32[radd] = DevMemory::read_rom_Int32(radd);
}
void DevMemory::copy_ram_to_rom_Int32(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_ULong(unsigned char radd, unsigned char fadd)
{
    DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
}
void DevMemory::copy_ram_to_rom_ULong(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_UInt32(radd, DevUInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Long(unsigned char radd, unsigned char fadd)
{
    DevInt32[radd] = DevMemory::read_rom_Int32(radd);
}
void DevMemory::copy_ram_to_rom_Long(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Int32(radd, DevInt32[fadd]);
}

void DevMemory::copy_rom_to_ram_Float(unsigned char radd, unsigned char fadd)
{
    DevFloat[radd] = DevMemory::read_rom_Float(radd);
}
void DevMemory::copy_ram_to_rom_Float(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Float(radd, DevFloat[fadd]);
}
void DevMemory::copy_rom_to_ram_Double(unsigned char radd, unsigned char fadd)
{
    DevDouble[radd] = DevMemory::read_rom_Double(radd);
}
void DevMemory::copy_ram_to_rom_Double(unsigned char fadd, unsigned char radd)
{
    DevMemory::write_rom_Double(radd, DevDouble[fadd]);
}
#endif