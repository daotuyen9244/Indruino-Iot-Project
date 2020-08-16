#include "SimpleModbusMaster_DUE.h"

//////////////////// Port information ///////////////////
#define baud 9600 //baudrate
#define timeout 1000 //timeout 
#define polling 200 // the scan rate
#define retry_count 10 //count scan



#define TOTAL_NO_OF_REGISTERS 3 //so luong thanh ghi dung

// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.
enum
{
  PACKET1,
  PACKET2,
  //PACKET3,
  TOTAL_NO_OF_PACKETS // leave this last entry
};


Packet packets[TOTAL_NO_OF_PACKETS]; //Packet to confiured


unsigned int regs[TOTAL_NO_OF_REGISTERS]= {0}; // array buffer cho thanh ghi tai master

void setup()
{
  // Initialize each packet
  //packet1 confiured with id slave =  1, function code Preset_multiple_register, addr of register =  1, count data = 2, array buffer address* = 0
  modbus_construct(&packets[PACKET1], 1, PRESET_MULTIPLE_REGISTERS, 1, 2, 0);

  //packet2 confiured with id slave = 2, function code force_single_coil, addr of coils = 0, count data =1, array buffer address* = 2;
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 0, 1, 2);

  // Initialize the Modbus Finite State Machine confiured modbus
  modbus_configure(&Serial, baud, timeout, polling, retry_count, packets, TOTAL_NO_OF_PACKETS, regs);
  
}

void loop()
{
  modbus_update();
  
  regs[0]=6; //set data at holding Register addr 1
  regs[1] = 5; //set data at holding Register addr 2
  regs[2] = 0xFF00; // set data at coils addr 0 
  // coils ON = 0xFF00, coils OFF = 0x0000; 
  //update data to be written to arduino slave

//test with multiway
}
