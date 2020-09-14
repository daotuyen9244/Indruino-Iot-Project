#include "ModbusSerial.h"
#include "Modbus.h"

ModbusSerial mb;
const int LAMP1_COIL = 1;
#define ledPin 25

void setup()
{

  mb.config(&Serial, 9600, SERIAL_8N1); //config modbus 
  
  mb.setSlaveId(1); //set slaveID
  
  mb.addCoil(LAMP1_COIL, false); //master can read/write
  
  mb.addIsts(LAMP1_COIL, false); //input register is only written by slave
  mb.addHreg(LAMP1_COIL, 0x01); //add holding register addr = lam1_coil with value = 0x01;
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, 0);

  
}

void loop()
{
  mb.task(); // keep alive
  digitalWrite(ledPin, mb.Coil(1));
  // put your main code here, to run repeatedly:
  //testing with multiway
}
