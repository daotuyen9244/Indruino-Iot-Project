#include "DevMemory.h"

void DevMemory::write_ram_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    for (uint16_t  t = 0; t < lens; t++)
    {
        *((char *)&MemMap + t) = *(data + t - add);
    }
}
uint8_t DevMemory::read_ram_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    for (uint16_t  t = add; t < lens; t++)
    {
        *(data + t - add) = *((char *)&MemMap + t);
    }
}
void DevMemory::write_ram_UChar(uint16_t add, uint8_t data)
{
    //MemMap.DevUChar[add] = data;
    //DevMemory::write_ram_Block(add,1,&data);
    write_ram(CData,add,data);
}
uint8_t DevMemory::read_ram_UChar(uint16_t add)
{
    uint8_t _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_Char(uint16_t add, int8_t data)
{
    //MemMap.Data[add] = data;
    write_ram(CData,add,data);
}
int8_t DevMemory::read_ram_Char(uint16_t add)
{
    int8_t _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_UInt(uint16_t add, uint16_t  data)
{
    write_ram(CData,add,data);
}
uint16_t  DevMemory::read_ram_UInt(uint16_t add)
{
    //return MemMap.DevUInt[add];
    uint16_t  _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_Int(uint16_t add, int16_t data)
{
    //MemMap.DevInt[add] = data;
    write_ram(CData,add,data);
}
int16_t DevMemory::read_ram_Int(uint16_t add)
{
    //return MemMap.DevInt[add];
    int16_t _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_UInt32(uint16_t add, uint32_t data)
{
    //MemMap.DevUInt32[add] = data;
    write_ram(CData,add,data);
}
uint32_t DevMemory::read_ram_UInt32(uint16_t add)
{
    uint32_t _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_Int32(uint16_t add, int32_t data)
{
    write_ram(CData,add,data);
}
int32_t DevMemory::read_ram_Int32(uint16_t add)
{
    int32_t _data=0x00;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_Float(uint16_t add, float data)
{
    write_ram(CData,add,data);
}
float DevMemory::read_ram_Float(uint16_t add)
{
    //return MemMap.DevFloat[add];
    float _data=0.0;
    read_ram(CData,add,_data);
    return _data;
}

void DevMemory::write_ram_Double(uint16_t add, double data)
{
    //MemMap.DevDouble[add] = data;
    write_ram(CData,add,data);
}
double DevMemory::read_ram_Double(uint16_t add)
{
    //return MemMap.DevDouble[add];
    double _data=0.0;
    read_ram(CData,add,_data);
    return _data;
}
bool DevMemory::setOutputAdd(uint16_t add, uint8_t lens)
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
bool DevMemory::setInputAdd(uint16_t add, uint8_t lens)
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
uint8_t DevMemory::InputAddBegin()
{
    return _InputStart;
}
uint8_t DevMemory::OutputAddBegin()
{
    return _OutputStart;
}
uint8_t DevMemory::InputLens()
{
    return _maxIn;
}
uint8_t DevMemory::OutputLens()
{
    return _maxOut;
}
uint8_t DevMemory::ReadInPut(uint16_t add)
{
    return MemMap.Data[_InputStart + add];
}
uint8_t DevMemory::ReadOutPut(uint16_t add)
{
    return MemMap.Data[_OutputStart + add];
}
bool DevMemory::WriteOutPut(uint16_t add, uint8_t data)
{
    if (add <= _maxOut) // Dem tu 0
    {
        MemMap.Data[_OutputStart + add] = data;
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
uint8_t DevMemory::readEPPROM(uint16_t add)
{
    return EEPROM.read(add);
}

void DevMemory::saveEPPROM()
{
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
bool DevMemory::writeEPPROM(uint16_t add, uint8_t data)
{
    EEPROM.write(add, data);
    DevMemory::saveEPPROM();
}
void DevMemory::write_rom_UChar(uint16_t add, uint8_t data)
{
    EEPROM.writeUChar(add, data);
    DevMemory::saveEPPROM();
}
uint8_t DevMemory::read_rom_UChar(uint16_t add)
{
    return EEPROM.readUChar(add);
}

void DevMemory::write_rom_Char(uint16_t add, int8_t data)
{
    EEPROM.writeChar(add + ECHAR_START, data);
    DevMemory::saveEPPROM();
}
int8_t DevMemory::read_rom_Char(uint16_t add)
{
    return EEPROM.readChar(add + ECHAR_START);
}

void DevMemory::write_rom_UInt(uint16_t add, uint16_t  data)
{
    EEPROM.writeUInt(add + EUINT_START, data);
    DevMemory::saveEPPROM();
}
uint16_t  DevMemory::read_rom_UInt(uint16_t add)
{
    return EEPROM.readUInt(add + EUINT_START);
}

void DevMemory::write_rom_Int(uint16_t add, int data)
{
    EEPROM.writeInt(add + EINT_START, data);
    DevMemory::saveEPPROM();
}
int16_t DevMemory::read_rom_Int(uint16_t add)
{
    return EEPROM.readInt(add + EINT_START);
}

void DevMemory::write_rom_UInt32(uint16_t add, uint32_t data)
{
    EEPROM.writeULong(add + EUINT32_START, data);
    DevMemory::saveEPPROM();
}
uint32_t DevMemory::read_rom_UInt32(uint16_t add)
{
    return EEPROM.readULong(add + EUINT32_START);
}

void DevMemory::write_rom_Int32(uint16_t add, int32_t data)
{
    EEPROM.writeLong(add + EINT32_START, data);
    DevMemory::saveEPPROM();
}
int32_t DevMemory::read_rom_Int32(uint16_t add)
{
    return EEPROM.readLong(add + EINT32_START);
}

void DevMemory::write_rom_Float(uint16_t add, float data)
{
    EEPROM.writeFloat(add + EFLOAT_START, data);
    DevMemory::saveEPPROM();
}
float DevMemory::read_rom_Float(uint16_t add)
{
    return EEPROM.readFloat(add + EFLOAT_START);
}

void DevMemory::write_rom_Double(uint16_t add, double data)
{
    EEPROM.writeDouble(add + EDBL_START, data);
    DevMemory::saveEPPROM();
}
double DevMemory::read_rom_Double(uint16_t add)
{
    return EEPROM.readDouble(add + EDBL_START);
}
void DevMemory::copy_rom_to_ram_UChar(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUChar[fadd] = DevMemory::read_rom_UChar(radd);
    DevMemory::write_ram_Block(fadd,1,(uint8_t*)(DevMemory::read_rom_UChar(radd)));
}
void DevMemory::copy_ram_to_rom_UChar(uint16_t fadd, uint16_t radd)
{
    uint8_t _data=0x00;
    DevMemory::read_ram_Block(fadd,1,(uint8_t*)_data);
    DevMemory::write_rom_UChar(radd, _data);
}

void DevMemory::copy_rom_to_ram_Char(uint16_t radd, uint16_t fadd)
{
    DevMemory::write_ram_Block(radd,1,(uint8_t*)(DevMemory::read_rom_Char(fadd)));
    //MemMap.Data[fadd] = DevMemory::read_rom_Char(radd);
}
void DevMemory::copy_ram_to_rom_Char(uint16_t fadd, uint16_t radd)
{
    int8_t _data=0x00;
    DevMemory::read_ram_Block(fadd,1,(uint8_t*)_data);
    DevMemory::write_rom_UChar(radd, _data);
}

void DevMemory::copy_rom_to_ram_UInt(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt[radd] = DevMemory::read_rom_UInt(radd);
    DevMemory::write_ram_Block(fadd,2,(uint8_t*)(DevMemory::read_rom_UInt(radd)));
}
void DevMemory::copy_ram_to_rom_Uint(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_UInt(radd, MemMap.DevUInt[fadd]);
    uint16_t _data=0x00;
    DevMemory::read_ram_Block(fadd,2,(uint8_t*)_data);
    DevMemory::write_rom_UInt(radd, _data);
}

void DevMemory::copy_rom_to_ram_Int(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt[radd] = DevMemory::read_rom_Int(radd);
    DevMemory::write_ram_Block(fadd,2,(uint8_t*)(DevMemory::read_rom_Int(radd)));
}
void DevMemory::copy_ram_to_rom_int(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_Int(radd, MemMap.DevInt[fadd]);
    int16_t _data=0x00;
    DevMemory::read_ram_Block(fadd,2,(uint8_t*)_data);
    DevMemory::write_rom_Int(radd, _data);
}

void DevMemory::copy_rom_to_ram_UInt32(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_rom_UInt32(radd)));
}
void DevMemory::copy_ram_to_rom_UInt32(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    uint32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_rom_UInt32(radd, _data);
}

void DevMemory::copy_rom_to_ram_Int32(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt32[radd] = DevMemory::read_rom_Int32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_rom_Int32(radd)));
}
void DevMemory::copy_ram_to_rom_Int32(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    int32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_rom_Int32(radd, _data);
}

void DevMemory::copy_rom_to_ram_ULong(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt32[radd] = DevMemory::read_rom_UInt32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_rom_UInt32(radd)));
}
void DevMemory::copy_ram_to_rom_ULong(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    uint32_t _data=0x00;
    DevMemory::read_ram_Block(radd,4,(uint8_t*)_data);
    DevMemory::write_rom_UInt32(fadd, _data);
}

void DevMemory::copy_rom_to_ram_Long(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt32[radd] = DevMemory::read_rom_Int32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_rom_Int32(radd)));
}
void DevMemory::copy_ram_to_rom_Long(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_Int32(radd, MemMap.DevInt32[fadd]);
    int32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_rom_Int32(radd, _data);
}

void DevMemory::copy_rom_to_ram_Float(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevFloat[radd] = DevMemory::read_rom_Float(radd);
    union {
        float a;
        uint8_t bytes[4];
    } thing;
    thing.a = DevMemory::read_rom_Float(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)thing.bytes);
}
void DevMemory::copy_ram_to_rom_Float(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_Float(radd, MemMap.DevFloat[fadd]);
    union {
        float a;
        uint8_t bytes[4];
    } thing;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)thing.bytes);
    DevMemory::write_rom_Float(radd, thing.a);
}
void DevMemory::copy_rom_to_ram_Double(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevDouble[radd] = DevMemory::read_rom_Double(radd);
    union {
        double a;
        uint8_t bytes[8];
    } thing;
    thing.a = DevMemory::read_rom_Double(radd);
    DevMemory::write_ram_Block(fadd,8,(uint8_t*)thing.bytes);
}
void DevMemory::copy_ram_to_rom_Double(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_rom_Double(radd, MemMap.DevDouble[fadd]);
     union {
        float a;
        uint8_t bytes[8];
    } thing;
    DevMemory::read_ram_Block(fadd,8,(uint8_t*)thing.bytes);
    DevMemory::write_rom_Float(radd, thing.a);
}
void DevMemory::write_rom_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    for (uint16_t  t = add; t < lens; t++)
    {
        EEPROM.write(t, *(data + (t - add)));
    }
#ifdef ESP32 || ESP8266
    EEPROM.commit();
#endif
}
uint8_t DevMemory::read_rom_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    for (uint16_t  t = add; t < lens; t++)
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
uint8_t DevMemory::readI2C_rom(uint16_t add)
{
    return eeprom.readByte(add);
}
bool DevMemory::writeI2C_rom(uint16_t add, uint8_t data)
{
    eeprom.writeByte(add, data);
}
void DevMemory::write_I2C_rom_UChar(uint16_t add, uint8_t data)
{
    eeprom.writeByte(add, data);
}
uint8_t DevMemory::read_I2C_rom_UChar(uint16_t add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_Char(uint16_t add, int8_t data)
{
    eeprom.writeByte(add, data);
}
int8_t DevMemory::read_I2C_rom_Char(uint16_t add)
{
    return eeprom.readByte(add);
}

void DevMemory::write_I2C_rom_UInt(uint16_t add, uint16_t  data)
{
    eeprom.writeBytes(add, 2, (uint8_t *)data);
}
uint16_t  DevMemory::read_I2C_rom_UInt(uint16_t add)
{
    uint16_t _x = 0;
    eeprom.readBytes(add, 2, (uint8_t *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int(uint16_t add, int data)
{
    eeprom.writeBytes(add, 2, (uint8_t *)data);
}
int16_t DevMemory::read_I2C_rom_Int(uint16_t add)
{
    int16_t _x = 0;
    eeprom.readBytes(add, 2, (uint8_t *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_UInt32(uint16_t add, uint32_t data)
{
    eeprom.writeBytes(add, 4, (uint8_t *)data);
}
uint32_t DevMemory::read_I2C_rom_UInt32(uint16_t add)
{
    uint32_t _x = 0;
    eeprom.readBytes(add, 4, (uint8_t *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Int32(uint16_t add, int32_t data)
{
    eeprom.writeBytes(add, 4, (uint8_t *)data);
}
int32_t DevMemory::read_I2C_rom_Int32(uint16_t add)
{
    int32_t _x = 0;
    eeprom.readBytes(add, 4, (uint8_t *)_x);
    return _x;
}

void DevMemory::write_I2C_rom_Float(uint16_t add, float data)
{
    union {
        float a;
        uint8_t bytes[4];
    } thing;
    thing.a = data;
    eeprom.writeBytes(add, 4, (uint8_t *)(thing.bytes));
}
float DevMemory::read_I2C_rom_Float(uint16_t add)
{
    float _x = 0;
    union {
        float a;
        uint8_t bytes[4];
    } thing;

    eeprom.readBytes(add, 4, (uint8_t *)(thing.bytes));
    _x = thing.a;
    return _x;
}

void DevMemory::write_I2C_rom_Double(uint16_t add, double data)
{
    union {
        double a;
        uint8_t bytes[8];
    } thing;
    thing.a = data;
    eeprom.writeBytes(add, 8, (uint8_t *)(thing.bytes));
}
double DevMemory::read_I2C_rom_Double(uint16_t add)
{
    double _x = 0;
    union {
        float a;
        uint8_t bytes[8];
    } thing;

    eeprom.readBytes(add, 8, (uint8_t *)(thing.bytes));
    _x = thing.a;
    return _x;
}
void DevMemory::copy_I2C_rom_to_ram_UChar(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUChar[fadd] = DevMemory::read_I2C_rom_UChar(radd);
    DevMemory::write_ram_Block(fadd,1,(uint8_t*)(DevMemory::read_I2C_rom_UChar(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_UChar(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_UChar(radd, MemMap.DevUChar[fadd]);
    uint8_t _data=0x00;
    DevMemory::read_ram_Block(fadd,1,(uint8_t*)_data);
    DevMemory::write_rom_UChar(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_Char(uint16_t radd, uint16_t fadd)
{
    //MemMap.Data[fadd] = DevMemory::read_I2C_rom_Char(radd);
    DevMemory::write_ram_Block(fadd,1,(uint8_t*)(DevMemory::read_I2C_rom_Char(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_Char(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_Char(radd, MemMap.Data[fadd]);
    int8_t _data=0x00;
    DevMemory::read_ram_Block(fadd,1,(uint8_t*)_data);
    DevMemory::write_I2C_rom_Char(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_UInt(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt[radd] = DevMemory::read_I2C_rom_UInt(radd);
    DevMemory::write_ram_Block(fadd,2,(uint8_t*)(DevMemory::read_I2C_rom_UInt(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_Uint(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_UInt(radd, MemMap.DevUInt[fadd]);
    uint16_t _data=0x00;
    DevMemory::read_ram_Block(fadd,2,(uint8_t*)_data);
    DevMemory::write_I2C_rom_UInt(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_Int(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt[radd] = DevMemory::read_I2C_rom_Int(radd);
    DevMemory::write_ram_Block(fadd,2,(uint8_t*)(DevMemory::read_I2C_rom_Int(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_int(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_Int(radd, MemMap.DevInt[fadd]);
    int16_t _data=0x00;
    DevMemory::read_ram_Block(fadd,2,(uint8_t*)_data);
    DevMemory::write_I2C_rom_Int(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_UInt32(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt32[radd] = DevMemory::read_I2C_rom_UInt32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_I2C_rom_UInt32(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_UInt32(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    uint32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_I2C_rom_UInt32(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_Int32(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt32[radd] = DevMemory::read_I2C_rom_Int32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_I2C_rom_Int32(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_Int32(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    int32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_I2C_rom_Int32(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_ULong(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevUInt32[radd] = DevMemory::read_I2C_rom_UInt32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_I2C_rom_UInt32(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_ULong(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_UInt32(radd, MemMap.DevUInt32[fadd]);
    uint32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_I2C_rom_UInt32(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_Long(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevInt32[radd] = DevMemory::read_I2C_rom_Int32(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)(DevMemory::read_I2C_rom_Int32(radd)));
}
void DevMemory::copy_ram_to_I2C_rom_Long(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_Int32(radd, MemMap.DevInt32[fadd]);
    int32_t _data=0x00;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)_data);
    DevMemory::write_I2C_rom_Int32(radd, _data);
}

void DevMemory::copy_I2C_rom_to_ram_Float(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevFloat[radd] = DevMemory::read_I2C_rom_Float(radd);
    union {
        double a;
        uint8_t bytes[4];
    } thing;
    thing.a = DevMemory::read_I2C_rom_Float(radd);
    DevMemory::write_ram_Block(fadd,4,(uint8_t*)thing.bytes);
}
void DevMemory::copy_ram_to_I2C_rom_Float(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_Float(radd, MemMap.DevFloat[fadd]);
    union {
        float a;
        uint8_t bytes[4];
    } thing;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)thing.bytes);
    DevMemory::write_I2C_rom_Float(radd, thing.a);
}
void DevMemory::copy_I2C_rom_to_ram_Double(uint16_t radd, uint16_t fadd)
{
    //MemMap.DevDouble[radd] = DevMemory::read_I2C_rom_Double(radd);
   //MemMap.DevDouble[radd] = DevMemory::read_rom_Double(radd);
    union {
        double a;
        uint8_t bytes[8];
    } thing;
    thing.a = DevMemory::read_I2C_rom_Double(radd);
    DevMemory::write_ram_Block(fadd,8,(uint8_t*)thing.bytes);
}
void DevMemory::copy_ram_to_I2C_rom_Double(uint16_t fadd, uint16_t radd)
{
    //DevMemory::write_I2C_rom_Double(radd, MemMap.DevDouble[fadd]);
    union {
        double a;
        uint8_t bytes[8];
    } thing;
    DevMemory::read_ram_Block(fadd,4,(uint8_t*)thing.bytes);
    DevMemory::write_I2C_rom_Float(radd, thing.a);
}
void DevMemory::write_I2C_rom_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    eeprom.writeBytes(add, lens, data);
}
uint8_t DevMemory::read_I2C_rom_Block(uint16_t add, uint16_t  lens, uint8_t *data)
{
    eeprom.readBytes(add, lens, data);
}
#endif
#endif