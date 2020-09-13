//**This is a lib which support for write another type of date**
#ifndef _ROM_H
#define _ROM_H
#include <Arduino.h>
#include <EEPROM.h>
#include "config_mem.h"

//ROM
class ROM
{
private:
    uint16_t sizeRom = 0; //size of Rom

    template <class T>
    T readAll(int add, T *des);
    template <class T>
    bool readAll(int add, uint8_t *des, size_t len);

    template <class T>
    bool writeAll(int add, T *value); //write data at add with len and write it to *p
    template <class T>
    bool writeAll(int add, uint8_t *ptr_value, size_t len);

public:
    friend class Indruino;
    friend class RamEeprom;
    void init();
    void init(int size);
    uint16_t getSize(uint16_t size);

    uint8_t readByte(int address);
    int8_t readChar(int address);
    uint8_t readUChar(int address);
    int16_t readShort(int address);
    uint16_t readUShort(int address);
    int32_t readInt(int address);
    uint32_t readUInt(int address);
    int32_t readLong(int address);
    uint32_t readULong(int address);
    int64_t readLong64(int address);
    uint64_t readULong64(int address);
    float readFloat(int address);
    double readDouble(int address);
    bool readBool(int address);
    size_t readString(int address, char *value, size_t maxLen);
    String readString(int address);
    size_t readBytes(int address, void *value, size_t maxLen);
    
    

    bool writeByte(int address, uint8_t value);
    bool writeChar(int address, int8_t value);
    bool writeUChar(int address, uint8_t value);
    bool writeShort(int address, int16_t value);
    bool writeUShort(int address, uint16_t value);
    bool writeInt(int address, int32_t value);
    bool writeUInt(int address, uint32_t value);
    bool writeLong(int address, int32_t value);
    bool writeULong(int address, uint32_t value);
    bool writeLong64(int address, int64_t value);
    bool writeULong64(int address, uint64_t value);
    bool writeFloat(int address, float value);
    bool writeDouble(int address, double value);
    bool writeBool(int address, bool value);
    bool writeString(int address, const char *value);
    bool writeString(int address, String value);
    bool writeBytes(int address, const void *value, size_t len);

    
    ROM();
    ~ROM();
};

extern ROM rom;
#endif //_ROM_H