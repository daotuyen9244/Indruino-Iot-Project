#include <Wire.h>
#include "heltec.h"
#include "DevMemory.h"
DevMemory myMemory;
DevMemoryMap UserMemMap;
DevMemoryMap UserMemMap1;
/// User define inout
#define SIZE_INPUT 8
#define IN0 0
#define IN1 255
#define IN2 255
#define IN3 255
#define IN4 255
#define IN5 255
#define IN6 255
#define IN7 255

#define SIZE_OUTPUT 8
#define OUT0 LED_BUILTIN
#define OUT1 255
#define OUT2 255
#define OUT3 255
#define OUT4 255
#define OUT5 255
#define OUT6 255
#define OUT7 255
char inputButton[SIZE_INPUT] = {IN0, IN1, IN2, IN3, IN4, IN5, IN6, IN7};
char outputControl[SIZE_INPUT] = {OUT0, OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7};

///
void setup()
{
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "Ten: ");
  Heltec.display->drawString(0, 10, "Sdt: ");
  Heltec.display->drawString(0, 20, "Mail:");
  
  
  Serial.println("____________________________");
  myMemory.write_ram_UChar(0, 10);
  Serial.println(myMemory.read_ram_UChar(0));

  myMemory.write_ram_Char(1, -99);
  Serial.println(myMemory.read_ram_Char(1));

  myMemory.write_ram_UInt(2, 100);
  Serial.println(myMemory.read_ram_UInt(2));

  myMemory.write_ram_Int(4, -100);
  Serial.println(myMemory.read_ram_Int(4));
  
  myMemory.write_ram_UInt32(6, 100);
  Serial.println(myMemory.read_ram_UInt32(6));

  myMemory.write_ram_Int32(10, -100);
  Serial.println(myMemory.read_ram_Int32(10));

  myMemory.write_ram_Float(14, 100.0);
  Serial.println(myMemory.read_ram_Float(14));
  myMemory.write_ram_Double(18, -99.9);
  Serial.println(myMemory.read_ram_Double(18));
  Serial.println("____________________________");
  
  //myMemory.get_ram_Int(0);
  String data = "";
  data = (String)EUCHAR_START + " " + ECHAR_START + " " + EUINT_START + " " + EINT_START + " " + EUINT32_START + " " + EINT32_START + " " + EFLOAT_START + " " + EDBL_START;

  Heltec.display->drawString(0, 30, data);
  Heltec.display->display();
  for (uint8_t i = 0; i < SIZE_INPUT; i++)
  {
    pinMode(inputButton[i], INPUT);
  }
  for (uint8_t i = 0; i < SIZE_OUTPUT; i++)
  {
    pinMode(outputControl[i], OUTPUT);
  }

  int sum = 0;
  Serial.print("Sizeof MemMap: ");
  Serial.println(sizeof(MemMap));

  for (int i = 0; i < sizeof(MemMap); i++)
  {
    *((char *)&MemMap + i) = i;
  }
  for (int i = 0; i < sizeof(MemMap); i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(*((char *)&MemMap + i), HEX);
  }
  Serial.println("print user mem map>>>>>>>>>>>>>>>>>> ");
  uint8_t diff = 0;
  myMemory.initEPPROM();
  myMemory.write_rom_Block(0, sizeof(MemMap), (unsigned char *)&MemMap);
  myMemory.read_rom_Block(0, sizeof(UserMemMap), (unsigned char *)&UserMemMap);
  for (int i = 0; i < sizeof(UserMemMap); i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(*((char *)&UserMemMap + i), HEX);
  }
  for (int i = 0; i < sizeof(UserMemMap); i++)
  {
    if (*((unsigned char *)&MemMap + i) != *((unsigned char *)&UserMemMap + i))
    {
      diff = 1;
    }
  }
  if (diff)
  {
    Serial.println("diff");
  }
  else
  {
    Serial.println("correct");
  }
#ifdef USE_ExI2C
  // Initiliaze EEPROM library.
  Serial.println("print user mem map BY i2c EPPROM>>>>>>>>>>>>>>>>>> ");
  myMemory.initI2CEPPROM();
  myMemory.write_I2C_rom_Block(0, sizeof(UserMemMap), (unsigned char *)&UserMemMap);
  myMemory.read_I2C_rom_Block(0, sizeof(UserMemMap1), (unsigned char *)&UserMemMap1);
  for (int i = 0; i < sizeof(UserMemMap1); i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.println(*((char *)&UserMemMap1 + i), HEX);
  }
  for (int i = 0; i < sizeof(UserMemMap1); i++)
  {
    //*((unsigned char *)&UserMemMap1 + i) +=1;
    if (*((unsigned char *)&UserMemMap + i) != *((unsigned char *)&UserMemMap1 + i))
    {
      diff = 1;
    }
  }
  if (diff)
  {
    Serial.println("diff");
  }
  else
  {
    Serial.println("correct");
  }
  Serial.println("test >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.");
  UserMemMap1.Data[0] = 99;
  setAddPointer(UserMemMap1);
  for (int i = 0; i < sizeof(UserMemMap1); i++)
  {
   Serial.println(*(CData+i),HEX);
  }
  
  float a =5.0,b=0.0;
  myMemory.write_I2C_rom_Float(0,a);
  b = myMemory.read_I2C_rom_Float(0);
  Serial.println(b);
  Serial.println(CData[6]);
  int n = 0;
  float _xxx =5.777;
  float kq=0.0;
   n = write_ram(CData,0, _xxx);
   //n = write_ram((uint8_t*)&(UserMemMap1.DevUChar[0]),0, _xxx);
   Serial.print("Wrote n byte: ");
   Serial.println(n);

   //n = read_ram(CData,0, kq);
   n = read_ram((uint8_t*)&(UserMemMap1),0, kq);
   Serial.print("Read n byte: ");
   Serial.println(n);
   Serial.print("kq: ");
   Serial.println(kq);
#endif

}


void loop()
{
  IPOProcess();
}
void IPOProcess()
{
  readInput();
  process();
  exportOutput();
}
void readInput()
{
  static long checkRTime = 0;
  uint8_t j = 0, k = 0;
  if (millis() - checkRTime > 150)
  {
    for (uint8_t i = 0; i < SIZE_INPUT; i++)
    {
      if (digitalRead(inputButton[i]))
      {
        //bitSet(MemMap.Data[_InputStart] ,i);
        MemMap.Data[_InputStart + k] |= 1 << j;
      }
      else
      {
        //bitClear(MemMap.Data[_InputStart] ,i);
        MemMap.Data[_InputStart + k] &= ~(1 << j);
      }
      j++;
      if (j > 7)
      {
        j = 0;
        k++;
      }
    }
    checkRTime = millis();
  }
}
void process()
{
  MemMap.Data[_OutputStart] = MemMap.Data[_InputStart];
}
void exportOutput()
{
  static long checkETime = 0;
  uint8_t j = 0, k = 0;
  if (millis() - checkETime > 150)
  {
    for (uint8_t i = 0; i < SIZE_OUTPUT; i++)
    {
      digitalWrite(outputControl[i], MemMap.Data[_OutputStart + k] & (0xff >> j));
      j++;
      if (j > 7)
      {
        j = 0;
        k++;
      }
    }
    checkETime = millis();
  }
}
