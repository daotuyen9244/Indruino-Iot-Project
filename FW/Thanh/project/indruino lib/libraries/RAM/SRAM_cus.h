#ifndef _SRAM_CUS_H
#define _SRAM_CUS_H

#include <Arduino.h>
#include "config_mem.h"

class SRAM
{
private:
    uint8_t *ptr = nullptr; // pointer data ram //dont change it
    uint16_t sizeRam = 0;   //size of Ram
    // //template for read
    // template <class T>
    // bool readAll(uint16_t add, T *des, uint16_t len); //read at add with len of data and copy data to *des
    // template <class T>
    // T readAll(uint16_t add, T &des);
    // //template for read

    // //template for write
    // template <class T>
    // bool writeAll(uint16_t add, T &value); //write data at add with len and write it to *p
    // template <class T>
    // bool writeAll(uint16_t add, uint8_t *ptr_value, uint16_t len);
    // //template for write
public:
    friend class Indruino;
    friend class RamEeprom;
    SRAM(void);
    SRAM(int size);
    void init(int size);
    uint16_t getSize();

    //add Function
    uint8_t *array(int address);
    //add Function

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

    template <class T>
    bool readAll(int add, T *des, size_t len); //read at add with len of data and copy data to *des
    template <class T>
    T readAll(int add, T &des);

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

    template <class T>
    bool writeAll(int add, T &value); //write data at add with len and write it to *p
    template <class T>
    bool writeAll(int add, uint8_t *ptr_value, size_t len);
};

extern SRAM ram;
#endif