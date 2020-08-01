#include <Wire.h>  
#include "heltec.h" 
#include "DevMemory.h"
DevMemory myMemory;
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
}

void loop() { }
