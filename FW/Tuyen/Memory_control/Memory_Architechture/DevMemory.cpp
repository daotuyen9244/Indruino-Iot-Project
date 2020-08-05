#include "DevMemory.h"

void write_ram_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = 0; t < lens; t++)
    {
        *((char *)&MemMap + t) = *(data + t - add);
    }
}
unsigned char read_ram_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    for (unsigned int t = add; t < lens; t++)
    {
        *(data + t - add) = *((char *)&MemMap + t);
    }
}

void DevMemory::write_ram_UChar(byte add, unsigned char data)
{
    MemMap.DevUChar[add] = data;
}
unsigned char DevMemory::read_ram_UChar(byte add)
{

    return MemMap.DevUChar[add];
}

void DevMemory::write_ram_Char(unsigned char add, char data)
{
    MemMap.DevChar[add] = data;
}
char DevMemory::read_ram_Char(unsigned char add)
{
    return MemMap.DevChar[add];
}

void DevMemory::write_ram_UInt(unsigned char add, unsigned int data)
{
    MemMap.DevUInt[add] = data;
}
unsigned int DevMemory::read_ram_UInt(unsigned char add)
{
    return MemMap.DevUInt[add];
}

void DevMemory::write_ram_Int(unsigned char add, int data)
{
    MemMap.DevInt[add] = data;
}
int DevMemory::read_ram_Int(unsigned char add)
{
    return MemMap.DevInt[add];
}

void DevMemory::write_ram_UInt32(unsigned char add, unsigned long data)
{
    MemMap.DevUInt32[add] = data;
}
unsigned long DevMemory::read_ram_UInt32(unsigned char add)
{
    return MemMap.DevUInt32[add];
}

void DevMemory::write_ram_Int32(unsigned char add, long data)
{
    MemMap.DevInt32[add] = data;
}
long DevMemory::read_ram_Int32(unsigned char add)
{
    return MemMap.DevInt32[add];
}

void DevMemory::write_ram_Float(unsigned char add, float data)
{
    MemMap.DevFloat[add] = data;
}
float DevMemory::read_ram_Float(unsigned char add)
{
    return MemMap.DevFloat[add];
}

void DevMemory::write_ram_Double(unsigned char add, double data)
{
    MemMap.DevDouble[add] = data;
}
double DevMemory::read_ram_Double(unsigned char add)
{
    return MemMap.DevDouble[add];
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
    return MemMap.DevChar[_InputStart + add];
}
unsigned char DevMemory::ReadOutPut(unsigned char add)
{
    return MemMap.DevChar[_OutputStart + add];
}
bool DevMemory::WriteOutPut(unsigned char add, unsigned char data)
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
void DevMemory::write_rom_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    //unsigned char _x=0;
    for (unsigned int t = add; t < lens; t++)
    {
        EEPROM.write(t, *(data + (t - add)));
        //_x = *(data +t-add);
        //EEPROM.write(t, _x);
        //Serial.print(t);
        //Serial.print("\t");
        //Serial.println(_x,HEX);
    }
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
unsigned char DevMemory::read_rom_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    //unsigned char _x=0;
    for (unsigned int t = add; t < lens; t++)
    {
        // _x = EEPROM.read(t);
        // *((char *)data + t-add) = _x;
        // Serial.print(t);
        // Serial.print("\t");
        // Serial.println(_x,HEX);
        *((char *)data + t - add) = EEPROM.read(t);
    }
}
#ifdef USE_ExI2C
bool DevMemory::initI2CEPPROM()
{
     eeprom.initialize();
    return 1;
}
unsigned char DevMemory::readI2C_rom(unsigned char add)
{
    return eeprom.readByte(add);
}
bool DevMemory::writeI2C_rom(unsigned char add, unsigned char data)
{
    eeprom.writeByte(add, data);
}
void DevMemory::write_I2C_rom_UChar(unsigned char add, unsigned char data)
{
    eeprom.writeByte(add, data);
}
unsigned char DevMemory::read_I2C_rom_UChar(unsigned char add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_Char(unsigned char add, char data)
{
    eeprom.writeByte(add, data);
}
char DevMemory::read_I2C_rom_Char(unsigned char add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_UInt(unsigned char add, unsigned int data)
{
    eeprom.writeBytes(add, 2, (byte*)data);
}
unsigned int DevMemory::read_I2C_rom_UInt(unsigned char add)
{
    uint16_t _x = 0;
    eeprom.readBytes(add,2,(byte*)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int(unsigned char add, int data)
{
    eeprom.writeBytes(add, 2, (byte*)data);
}
int DevMemory::read_I2C_rom_Int(unsigned char add)
{
    int16_t _x = 0;
    eeprom.readBytes(add,2,(byte* )_x);
    return _x;
}

void DevMemory::write_I2C_rom_UInt32(unsigned char add, unsigned long data)
{
    eeprom.writeBytes(add, 4, (byte* )data);
}
unsigned long DevMemory::read_I2C_rom_UInt32(unsigned char add)
{
    uint32_t _x = 0;
    eeprom.readBytes(add,4,(byte* )_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int32(unsigned char add, long data)
{
    eeprom.writeBytes(add, 4, (byte* )data);
}
long DevMemory::read_I2C_rom_Int32(unsigned char add)
{
    int32_t _x = 0;
    eeprom.readBytes(add,4,(byte* )_x);
    return _x;
}

void DevMemory::write_I2C_rom_Float(unsigned char add, float data)
{
    char my_array[10];
    
     *( (float*)(my_array + 3) )= data;           // from array to float
    eeprom.writeBytes(add, 4, (byte*)my_array);
}
float DevMemory::read_I2C_rom_Float(unsigned char add)
{
    float _x = 0;
    char my_array[10];
    eeprom.readBytes(add, 4, (byte*)my_array);
    _x=  *( (float*)(my_array + 3) );           // from array to float
    return _x;
}

void DevMemory::write_I2C_rom_Double(unsigned char add, double data)
{
    char my_array[10];
    
     *( (double*)(my_array + 7) )= data;           // from array to float
    eeprom.writeBytes(add, 8, (byte*)my_array);
}
double DevMemory::read_I2C_rom_Double(unsigned char add)
{
    
    double _x = 0;
    char my_array[10];
    
    eeprom.readBytes(add, 8, (byte*)my_array);
    _x=  *( (float*)(my_array + 3) );           // from array to float
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
void DevMemory::write_I2C_rom_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    eeprom.writeBytes(add, lens, data);
}
unsigned char DevMemory::read_I2C_rom_Block(unsigned char add, unsigned int lens, unsigned char *data)
{
    eeprom.readBytes(add, lens, data);
}
#endif
#endif