#include <Wire.h>  
#include "heltec.h" 

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0,0,"Ten: Phan Hoang Anh Tuan");  
  Heltec.display->drawString(0,10,"Sdt: 0368474344");
  Heltec.display->drawString(0,20,"Mail: anhtuan23298@gmail.com");
  Heltec.display->display();
}

void loop() { }
