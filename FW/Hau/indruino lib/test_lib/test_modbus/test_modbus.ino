// #include "ModbusMaster.h"


// // instantiate ModbusMaster object
// ModbusMaster node;


// void setup()
// {
//   // use Serial (port 0); initialize Modbus communication baud rate
//   Serial.begin(19200);

//   // communicate with Modbus slave ID 2 over Serial (port 0)
//   node.begin(2, Serial);
// }


// void loop()
// {
//   static uint32_t i;
//   uint8_t j, result;
//   uint16_t data[6];

//   i++;

//   // set word 0 of TX buffer to least-significant word of counter (bits 15..0)
//   node.setTransmitBuffer(0, lowWord(i));

//   // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
//   node.setTransmitBuffer(1, highWord(i));

//   // slave: write TX buffer to (2) 16-bit registers starting at register 0
//   result = node.writeMultipleRegisters(0, 2);

//   // slave: read (6) 16-bit registers starting at register 2 to RX buffer
//   result = node.readHoldingRegisters(2, 6);

//   // do something with data if read is successful
//   if (result == node.ku8MBSuccess)
//   {
//     for (j = 0; j < 6; j++)
//     {
//       data[j] = node.getResponseBuffer(j);
//     }
//   }
// }



//////////////////


#include "SimpleModbusMaster_DUE.h"
//////////////////// Port information ///////////////////
#define baud 9600 //baudrate
#define timeout 1000 //timeout 
#define polling 200 // the scan rate
#define retry_count 10 //count scan
#define TOTAL_NO_OF_REGISTERS 50 //so luong thanh ghi dung
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


uint16_t regs[TOTAL_NO_OF_REGISTERS]= {0}; // array buffer cho thanh ghi tai master

void setup()
{
  // Initialize each packet
  //packet1 confiured with id slave =  1, function code Preset_multiple_register, addr of register =  0, count data = 2, array buffer address* = 0
  modbus_construct(&packets[PACKET1], 1, PRESET_MULTIPLE_REGISTERS, (uint16_t)0, (uint16_t)50, (uint16_t)0);

  //packet2 confiured with id slave = 2, function code force_single_coil, addr of coils = 0, count data =1, array buffer address* = 2;
 // modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 0, 1, 2);

  // Initialize the Modbus Finite State Machine confiured modbus
  modbus_configure(&Serial, baud, timeout, polling, retry_count, 255,packets, TOTAL_NO_OF_PACKETS, regs);
  
}

void loop()
{
  modbus_update();
  
  //regs[0]=6; //set data at holding Register addr 1
 // regs[1] = 5; //set data at holding Register addr 2
  regs[14] = 0xFFFF; // set data at coils addr 0 
  //coils ON = 0xFF00, coils OFF = 0x0000; 
  //update data to be written to arduino slave

//test with multiway
}