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

  int bufsize=25;
  char buf[bufsize] = "vn-- indruino";
  //ram.writeString(50, buf);
  char buf1[bufsize];

  /*ram.readString(50,buf1,bufsize);
  Serial.println(buf1);*/
  //Serial.println(ram.readString(5));
  
  ram.writeBytes(100,buf,bufsize);
  ram.readBytes(100, buf1, bufsize);
  Serial.println(ram.readString(100));
  
  //String sentence = "I love ESP32.";
  //ram.writeString(20, sentence);
  //Serial.println(ram.readString(20));

  //////////////////////////////////
  //TEST WRITE
  
  //ram.writeByte(0, 69);
  //ram.writeChar(0, 99);
  //ram.writeUChar(0,253);
  //ram.writeShort(0, value);
  //ram.writeUShort(0,65535);
  //ram.writeInt(0,123456789);
  //ram.writeLong(0,211111112);
  //ram.writeULong(0,3000000000);

  /*int64_t value=11111122;
  ram.writeLong64(0,value);*/

  /*uint64_t value=9922;
  ram.writeULong64(0,value);*/

  //ram.writeFloat(0,1.1222);
  //ram.writeDouble(0,6.664);
  //ram.writeBool(0,10);
  //String demo="esp 32";
  //ram.writeString(0, demo);
  //////////////////////////////////


  //////////////////////////////////
  //TEST READ

  //Serial.println(EEPROM.read(0));
  //Serial.println(ram.readByte(0));
  //Serial.println(ram.readChar(0));
  //Serial.println(ram.readUChar(0));
  //Serial.println(ram.readShort(0));
  //Serial.println(ram.readUShort(0));
  //Serial.println(ram.readInt(0));
  //Serial.println(ram.readLong(0));
  //Serial.println(ram.readULong(0));
  
  /*value=0;
  value = ram.readLong64(0);
  Serial.printf("0x%08X", (uint32_t)(value >> 32));
  Serial.printf("%08X\n", (uint32_t)value);*/

  
  /*value=0;
  value = ram.readULong64(0);
  Serial.printf("0x%08X", (uint32_t)(value >> 32));
  Serial.printf("%08X\n", (uint32_t)value);*/

  //Serial.println(ram.readFloat(0),4);
  //Serial.println(ram.readDouble(0),3);
  //Serial.println(ram.readBool(0));
  //Serial.println(ram.readString(10));
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
