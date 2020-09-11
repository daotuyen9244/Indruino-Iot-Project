#include <EEPROM.h>
#include "indruino_data.h" 

RamEeprom syn;

void setup()
{

  Serial.begin(115200);
  while (!Serial);
  rom.init();
  ram.init(512);
  syn.init();
  


  rom.writeByte(0,77);
  //syn.write2RomByte(0,0);
  //syn.write2RamByte(0,0);
  //Heltec.display->drawString(30,30,String(ram.readByte(0)));
  //Heltec.display->drawString(30,50,String(rom.readByte(0)));
 // Heltec.display->display();


  //////////////////////////////////

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