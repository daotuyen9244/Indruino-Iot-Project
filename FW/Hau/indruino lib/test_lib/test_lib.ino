#include <EEPROM.h>
#include "indruino_data.h"

RamEeprom syn;
//SRAM newRam(512);

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  rom.init();
  ram.init(512);
  syn.init();
  int16_t value = 1052;
  int16_t value_data = 1024;
  //ram.writeShort(0, value_data);
  //rom.writeShort(0, value);
  syn.write2RamShort(0, 0);
  //Serial.println(EEPROM.read(0));
  Serial.println(ram.readShort(0));
  // ram.init(512);
  // syn.init();
  // syn.setRam(newRam);
  // syn.resetRam();
  // int16_t value = 1037;
  // ram.writeShort(0, value);
  // Serial.println(ram.readShort(0));
  // Serial.println(rom.readByte(0));
  // uint8_t temp = 0;
  // uint16_t pos = 0;
  // syn.write2RomShort(pos, pos);
  
  // Serial.println(rom.readShort(pos));

//  syn.write2RamShort(0,0);

//  Serial.println(rom.readShort(0));

  
  //rom.writeByte(0, value);
  //Serial.println(rom.readByte(0));
  
  // uint8_t test = 11;
  // rom.writeByte(0, test);;

  // Serial.begin(9600);
  // while(!Serial);
  // Serial.println(rom.readByte(0));
}

void loop()
{

  // put your main code here, to run repeatedly:
}