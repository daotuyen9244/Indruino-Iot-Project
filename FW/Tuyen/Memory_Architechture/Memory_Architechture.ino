#include <Wire.h>  
#include "heltec.h" 
#include "DevMemory.h"
DevMemory myMemory;

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
char inputButton[SIZE_INPUT]={IN0,IN1,IN2,IN3,IN4,IN5,IN6,IN7};
char outputControl[SIZE_INPUT]={OUT0,OUT1,OUT2,OUT3,OUT4,OUT5,OUT6,OUT7};
///
void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0,0,"Ten: ");  
  Heltec.display->drawString(0,10,"Sdt: ");
  Heltec.display->drawString(0,20,"Mail:");
  myMemory.write_ram_Int(0,-100);
  //myMemory.get_ram_Int(0);
  String data ="";
  data = (String) EUCHAR_START  +" " +ECHAR_START +" " +EUINT_START +" " +EINT_START +" " +EUINT32_START+" " +EINT32_START+" " +EFLOAT_START+" " +EDBL_START ;
  
  Heltec.display->drawString(0,30,data);
  Heltec.display->display();
  for(byte i=0;i<SIZE_INPUT;i++)
  {
    pinMode(inputButton[i],INPUT);
  }
  for(byte i=0;i<SIZE_OUTPUT;i++)
  {
    pinMode(outputControl[i],OUTPUT);
  }
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
  static long checkRTime=0;
  byte j=0,k=0;
  if(millis() - checkRTime > 150)
  {
    for(byte i=0;i<SIZE_INPUT;i++)
    {
      if(digitalRead(inputButton[i]))
      {
        //bitSet(DevUChar[_InputStart] ,i);
        DevUChar[_InputStart+k] |= 1<<j;
      }
      else
      {
        //bitClear(DevUChar[_InputStart] ,i);
        DevUChar[_InputStart+k] &= ~(1<<j);
      }
      j++;
      if(j>7)
      {
        j=0;
        k++;
      }
    }
    checkRTime = millis();
  }
}
void process()
{
  DevUChar[_OutputStart] = DevUChar[_InputStart]  ;
}
void exportOutput()
{
  static long checkETime=0;
  byte j=0,k=0;
  if(millis() - checkETime > 150)
  {
    for(byte i=0;i<SIZE_OUTPUT;i++)
    { 
      digitalWrite(outputControl[i],DevUChar[_OutputStart+k]&(0xff >> j));
      j++;
      if(j>7)
      {
        j=0;
        k++;
      }
    }
    checkETime = millis();
  }
}