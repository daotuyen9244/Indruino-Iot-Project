//#include <EEPROM.h>
#include "indruino_data.h"

Indruino indruino;
//SRAM newRam(512);

void setup()
{
  indruino.init();
  Serial.begin(9600);
  while (!Serial);

  // int16_t value = 1052;
  
  // indruino.synMyData()->loadRom2Ram(0, 0, 4);
  
  // //ram.writeShort(0, value_data);
  
  //Serial.println(EEPROM.read(0));
  const char* tmp = "testing";
  indruino.myRom()->writeString(0,tmp);
  char buffer[100] = {0};
  indruino.myRom()->readString(0, buffer, 7);

  String aa = String(buffer);
  Serial.begin(9600);
  Serial.println(aa);
  //Serial.println(indruino.myRam()->readShort(2));
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
