#include "SRAM_cus.h"



uint16_t SRAM::getSize() {
    uint16_t temp = sizeRam;
    return temp;
}

//init
void SRAM::init(int size)
{
    if (ptr != nullptr)
        return;

    if (size <= 0)
        return;

    if (sizeRam == 0)
        sizeRam = size;

    ptr = (uint8_t *)calloc(sizeRam, sizeof(uint8_t));
}
//init

//
SRAM::SRAM(int size)
{
    if (ptr != nullptr)
        return;

    if (size <= 0)
        return;

    if (sizeRam == 0)
        sizeRam = size;

    ptr = (uint8_t *)calloc(sizeRam, sizeof(uint8_t));
}
//
//
SRAM::SRAM(void)
{
}
//
//template for read
template <class T>
bool SRAM::readAll(int add, T *des, size_t len)
{
    if ((add < 0) || (add >= sizeRam))
        return false;
    memcpy(des, ptr + add, len);
    return true;
}

template <class T>
T SRAM::readAll(int add, T &des)
{
    if ((add < 0) || (add >= sizeRam))
        return 0;
    memcpy(&des, ptr + add, sizeof(T));
    return des;
}
//template for read

//template for write
template <typename T>
bool SRAM::writeAll(int add, T &value)
{
    if ((add < 0) || (add >= sizeRam))
        return false;
    memcpy(ptr + add, &value, sizeof(T));
    return true;
}

template <class T>
bool SRAM::writeAll(int add, uint8_t *ptr_value, size_t len)
{
    if ((add < 0) || (add >= sizeRam))
        return false;
    memcpy(ptr + add, ptr_value, len);
    return true;
}
//template for write

//WRITE

//writeByte
bool SRAM::writeByte(int address, uint8_t value)
{
    return writeAll(address, value);
}
//writeByte

//writeChar
bool SRAM::writeChar(int address, int8_t value)
{
    return writeAll(address, value);
}
//writeChar

//writeUChar
bool SRAM::writeUChar(int address, uint8_t value)
{
    return writeAll(address, value);
}
//writeUChar

//writeShort
bool SRAM::writeShort(int address, int16_t value) {
    return writeAll(address, value);
}
//writeShort

//writeUShort
bool SRAM::writeUShort(int address, uint16_t value)
{
    return writeAll(address, value);
}
//writeUShort

//writeInt
bool SRAM::writeInt(int address, int32_t value)
{
    return writeAll(address, value);
}
//writeInt

//writeUInt
bool SRAM::writeUInt(int address, uint32_t value)
{
    return writeAll(address, value);
}
//writeUInt

//writeLong
bool SRAM::writeLong(int address, int32_t value)
{
    return writeAll(address, value);
}
//writeLong

//writeULong
bool SRAM::writeULong(int address, uint32_t value)
{
    return writeAll(address, value);
}
//writeULong

//writeLong64
bool SRAM::writeLong64(int address, int64_t value)
{
    return writeAll(address, value);
}
//writeLong64

//writeULong64
bool SRAM::writeULong64(int address, uint64_t value)
{
    return writeAll(address, value);
}
//writeULong64

//writeFloat
bool SRAM::writeFloat(int address, float value)
{
    return writeAll(address, value);
}
//writeFloat

//writeDouble
bool SRAM::writeDouble(int address, double value)
{
    return writeAll(address, value);
}
//writeDouble

//writeBool
bool SRAM::writeBool(int address, bool value)
{
    int8_t Bool;
    value ? Bool = 1 : Bool = 0;
    return writeAll(address, Bool);
}
//writeBool

//writeString
bool SRAM::writeString (int address, const char* value)
{
  if (!value)
    return 0;

  if (address < 0 || address > sizeRam)
    return 0;

  uint16_t len;
  for (len = 0; len <= sizeRam; len++)
    if (value[len] == 0)
      break;

  if (address + len > sizeRam)
    return 0;

  memcpy(ptr + address, (const uint8_t*) value, len + 1);
  return strlen(value);
}
//writeString

//
bool SRAM::writeString(int address, String value)
{
    return SRAM::writeString (address, value.c_str());
}
//

//writeBytes
bool SRAM::writeBytes(int address, const void *value, size_t len)
{
    if (!value || !len)
    return 0;

    if (address < 0 || address + len > sizeRam)
        return 0;

    memcpy(ptr + address, (const void*) value, len);
    return len;
}
//writeBytes

//WRITE



//READ

//readByte
uint8_t SRAM::readByte(int address)
{
    uint8_t temp;
    return readAll(address, temp);
}
//readByte

//readChar
int8_t SRAM::readChar(int address)
{
    int8_t temp;
    return readAll(address, temp);
}
//readChar

//readUChar
uint8_t SRAM::readUChar(int address)
{
    uint8_t temp;
    return readAll(address, temp);
}
//readUChar

//readShort
int16_t SRAM::readShort(int address) 
{
    int16_t temp;
    return readAll(address, temp);
}
//readShort

//readUShort
uint16_t SRAM::readUShort(int address)
{
    uint16_t temp;
    return readAll(address, temp);
}
//readUShor

//readInt
int32_t SRAM::readInt(int address)
{
    int32_t temp;
    return readAll(address, temp);
}
//readInt

//readUInt
uint32_t SRAM::readUInt(int address)
{
    uint32_t temp;
    return readAll(address, temp);
}
//readUInt

//readLong
int32_t SRAM::readLong(int address)
{
    int32_t temp;
    return readAll(address, temp);
}
//readLong

//readULong
uint32_t SRAM::readULong(int address)
{
    uint32_t temp;
    return readAll(address, temp);
}
//readULong

//readLong64
int64_t SRAM::readLong64(int address)
{
    int64_t temp;
    return readAll(address, temp);
}
//readLong64

//readULong64
uint64_t SRAM::readULong64(int address)
{
    uint64_t temp;
    return readAll(address, temp);
}
//readULong64

//readFloat
float SRAM::readFloat(int address)
{
    float temp;
    return readAll(address, temp);
}
//readFloat

//readDouble
double SRAM::readDouble(int address)
{
    double temp;
    return readAll(address, temp);
}
//readDouble

//readBool
bool SRAM::readBool(int address)
{
    int8_t tamp;
    return readAll(address, tamp) ? 1 : 0;
}
//readBool

//readString
size_t SRAM::readString (int address, char* value, size_t maxLen)
{
  if (!value)
    return 0;

  if (address < 0 || address + maxLen > sizeRam)
    return 0;

  uint16_t len;
  for (len = 0; len <= sizeRam; len++)
    if (ptr[address + len] == 0)
      break;

  if (address + len > sizeRam)
    return 0;

  memcpy((uint8_t*) value, ptr + address, len);
  value[len] = 0;
  return len;
}
//readString

//
String SRAM::readString (int address)
{
  if (address < 0 || address > sizeRam)
    return String();

  uint16_t len;
  for (len = 0; len <=sizeRam; len++)
    if (ptr[address + len] == 0)
      break;

  if (address + len > sizeRam)
    return String();

  char value[len];
  memcpy((uint8_t*) value, ptr + address, len);
  value[len] = 0;
  return String(value);
}
//

//
size_t SRAM::readBytes(int address, void *value, size_t maxLen)
{
    if (!value || !maxLen)
    return 0;

  if (address < 0 || address + maxLen > sizeRam)
    return 0;

  memcpy((void*) value, ptr + address, maxLen);
  return maxLen;
}
//
//READ



SRAM ram;

