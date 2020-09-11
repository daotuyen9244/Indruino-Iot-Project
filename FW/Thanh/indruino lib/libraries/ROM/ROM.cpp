#include "ROM.h"
#include <Arduino.h>
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
//readLong this ROM
int32_t ROM::readLong(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readLong(address);
#else
    uint32_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readLong this ROM
//readULong this ROM
uint32_t ROM::readULong(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readULong(address);
#else
    uint32_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readULong this ROM
//readLong64 this ROM
int64_t ROM::readLong64(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readLong64(address);
#else
    int64_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readLong64 this ROM
//readULong64 this ROM
uint64_t ROM::readULong64(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readULong64(address);
#else
    uint64_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readULong64 this ROM
//readChar this ROM
int8_t ROM::readChar(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readChar(address);
#else
    int8_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readChar this ROM
//readUChar this ROM
uint8_t ROM::readUChar(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readUChar(address);
#else
    uint8_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readChar this ROM
//readUShort this ROM
uint16_t ROM::readUShort(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readUShort(address);
#else
    uint16_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readShort this ROM
//readInt this ROM
int32_t ROM::readInt(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readInt(address);
#else
    int32_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readInt this ROM
//readUInt this ROM
uint32_t ROM::readUInt(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readUInt(address);
#else
    int32_t temp = 0;
    return readAll(address, &temp);
#endif
}
//readUInt this ROM
//readFloat this ROM
float ROM::readFloat(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readFloat(address);
#else
    float temp = 0;
    return readAll(address, &temp);
#endif
}
//readFloat this ROM
//readDouble this ROM
double ROM::readDouble(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readDouble(address);
#else
    double temp = 0;
    return readAll(address, &temp);
#endif
}
//readDouble this ROM
//readBool this ROM
bool ROM::readBool(int address)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readBool(address);
#else
    bool temp = 0;
    return readAll(address, &temp) ? 1 : 0;
#endif
}
//readBool this ROM
//readString
size_t ROM::readString (int address, char* value, size_t maxLen)
{
 #ifdef ESP32 || ESP8266
    return EEPROM.readString(address, value, maxLen);
#else  
  uint16_t len;
  for (len = 0; len <= sizeRom; len++)
    if (ptr[address + len] == 0)
      break;

  if (address + len > sizeRom)
    return 0;

  memcpy((uint8_t*) value, ptr + address, len);
  value[len] = 0;
  return len;
  #endif
}
//readString
//readString this ROM
String ROM::readString (int address)
{
 #ifdef ESP32 || ESP8266
    return EEPROM.readString(address);
#else  
  uint16_t len;
  for (len = 0; len <=sizeRom; len++)
    if (ptr[address + len] == 0)
      break;

  if (address + len > sizeRom)
    return String();

  char value[len];
  memcpy((uint8_t*) value, ptr + address, len);
  value[len] = 0;
  return String(value);
 #endif
}
//readString this ROM
//
size_t ROM::readBytes(int address, void *value, size_t maxLen)
{
#ifdef ESP32 || ESP8266
    return EEPROM.readBytes(address,value,maxLen);
#else  
    if (!value || !maxLen)
    return 0;

  if (address < 0 || address + maxLen > sizeRam)
    return 0;

  memcpy((void*) value, ptr + address, maxLen);
  return maxLen;
#endif
}
//
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
//writeLong this ROM
bool ROM::writeLong(int address, int32_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeLong(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeLong this ROM
//writeULong this ROM
bool ROM::writeULong(int address, uint32_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeULong(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeULong this ROM
//writeLong64 this ROM
bool ROM::writeLong64(int address, int64_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeLong64(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeLong64 this ROM
//writeULong64 this ROM
bool ROM::writeULong64(int address, uint64_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeULong64(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeULong64 this ROM
//writeChar this ROM
bool ROM::writeChar(int address, int8_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeChar(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeChar this ROM
//writeUChar this ROM
bool ROM::writeUChar(int address, uint8_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeUChar(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeChar this ROM
//writeUShort this ROM
bool ROM::writeUShort(int address, uint16_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeUShort(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeUShort this ROM
//writeInt this ROM
bool ROM::writeInt(int address, int32_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeInt(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeInt this ROM
//writeUInt this ROM
bool ROM::writeUInt(int address, uint32_t value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeUInt(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeUInt this ROM
//writeFloat this ROM
bool ROM::writeFloat(int address, float value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeFloat(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeFloat this ROM
//writeDouble this ROM
bool ROM::writeDouble(int address, double value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeDouble(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeDouble this ROM
//writeBool this ROM
bool ROM::writeBool(int address, bool value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeBool(address, value);
    return EEPROM.commit();
#else
    return writeAll(address, &value);
#endif
}
//writeBool this ROM
//writeString
bool ROM::writeString (int address, const char* value)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeString(address, value);
    return EEPROM.commit();
#else  
  uint16_t len;
  for (len = 0; len <= sizeRom; len++)
    if (value[len] == 0)
      break;

  if (address + len > sizeRom)
    return 0;
 memcpy(ptr + address, (const uint8_t*) value, len + 1);
 
  return strlen(value);
  #endif
}
//writeString
//
bool ROM::writeString(int address, String value)
{
    return ROM::writeString (address, value.c_str());
}
//
//writeBytes
bool ROM::writeBytes(int address, const void *value, size_t len)
{
#ifdef ESP32 || ESP8266
    EEPROM.writeBytes(address, value, len);
    return EEPROM.commit();
#else  
    if (address < 0 || address + len > sizeRom)
        return 0;

    memcpy(ptr + address, (const void*) value, len);
    return len;
#endif
}
//writeBytes
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