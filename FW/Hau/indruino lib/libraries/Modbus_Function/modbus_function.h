#ifndef MODBUS_FUNCTION_H
#define MODBUS_FUNCTION_H

#include "indruino_data.h"
#include "ModbusMaster.h"
//#####################################################################

//convert 2 byte type -> 1 byte type array (2 members)
typedef union cv_
{
  byte tmp[2];
  uint16_t value = 0x00;
} CV_;
//convert 2 byte type -> 1 byte type array (2 members)

//convert 2 byte array -> 1 byte array
typedef union convert
{
  byte *_byteAr;
  uint16_t *_uintAr;
} CONVERT;
//convert 2 byte array -> 1 byte array

//#######################################################################
#define sizeUint8_t 100
#define sizeRegs 50
//data backup
uint16_t au16data[sizeRegs] = {0};
//data backup
class MyModbus : public ModbusMaster
{
private:
  /* data */
public:
  void init(uint8_t id, uint16_t baud, Stream &serial);
  bool writeByte_modbus(uint16_t addr, uint8_t data);
  bool writeUShort_modbus(uint16_t addr, uint16_t data);
  uint8_t readByte_modbus(uint16_t addr);
  uint16_t readUShort_modbus(uint16_t addr);
  void readData();
  MyModbus(/* args */);
  ~MyModbus();
};

MyModbus::MyModbus(/* args */)
{
}
MyModbus::~MyModbus()
{
}

//#######################################################################
void MyModbus::init(uint8_t id, uint16_t baud, Stream &serial) //initialize
{
  this->begin(id, serial);
}

bool MyModbus::writeByte_modbus(uint16_t addr, uint8_t data)
{
  if (addr > _SIZE_OF_RAM)
    return 0;

  uint16_t tmp = 0;
  CV_ cv_byte;
  readHoldingRegisters(addr / 2, 1);
  tmp = this->getResponseBuffer(0);
  cv_byte.value = tmp;
  if (addr % 2 == 0)
  {
    cv_byte.tmp[0] = data;
  }
  else
  {
    cv_byte.tmp[1] = data;
  }
  this->writeSingleRegister(addr / 2, cv_byte.value);
  return 1;
}
bool MyModbus::writeUShort_modbus(uint16_t addr, uint16_t data)
{
  if (addr > _SIZE_OF_RAM - 1)
    return 0;
  CV_ cv_byte;
  cv_byte.value = data;
  if (addr % 2 == 0)
  {
    this->writeSingleRegister(addr / 2, data);
    return 1;
  }
  else
  {
    this->writeByte_modbus(addr, cv_byte.tmp[0]);
    this->writeByte_modbus(addr, cv_byte.tmp[1]);
    return 1;
  }
}

uint8_t MyModbus::readByte_modbus(uint16_t addr)
{
  if (addr > _SIZE_OF_RAM)
    return 0;
  CV_ cv_byte;
  uint16_t tmp = 0;
  this->readHoldingRegisters(addr / 2, 1);
  tmp = this->getResponseBuffer(0);
  cv_byte.value = tmp;
  if (addr % 2 == 0)
  {
    return cv_byte.tmp[0];
  }
  else
  {
    return cv_byte.tmp[1];
  }
}
uint16_t MyModbus::readUShort_modbus(uint16_t addr)
{
  if (addr > _SIZE_OF_RAM - 1)
    return 0;
  CV_ cv_byte;
  uint16_t tmp = 0;
  if (addr % 2 == 0)
  {
    this->readHoldingRegisters(addr / 2, 1);
    tmp = this->getResponseBuffer(0);
    return tmp;
  }
  else
  {
    cv_byte.tmp[0] = this->readByte_modbus(addr);
    cv_byte.tmp[1] = this->readByte_modbus(addr + 1);
    tmp = cv_byte.value;
    return tmp;
  }
}

void MyModbus::readData() //read all data from modbus reg
{
    for (uint16_t count = 0; count < sizeRegs; count+=2)
    {
      au16data[count] = this->readUShort_modbus(count);
      ram.writeUShort(count, au16data[count]);
    }
}
//#######################################################################


MyModbus modbus;
#endif //MODBUS_FUNCTION_H