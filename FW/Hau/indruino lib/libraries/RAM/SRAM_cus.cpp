#include "SRAM_cus.h"



uint16_t SRAM::getSize() {
    uint16_t temp = sizeRam;
    return temp;
}

uint8_t* SRAM::array(int address) {
       return (ptr+address);
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

//write
//writeByte
bool SRAM::writeByte(int address, uint8_t value)
{
    return writeAll(address, value);
}
//writeByte
//writeShort
bool SRAM::writeShort(int address, int16_t value) {
    return writeAll(address, value);
}
//writeShort
//write

//read
//readByte
uint8_t SRAM::readByte(int address)
{
    uint8_t temp;
    return readAll(address, temp);
}
//readByte
//readShort
int16_t SRAM::readShort(int address) {
    uint16_t temp;
    return readAll(address, temp);
}
//readShort

//read



SRAM ram;



