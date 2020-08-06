#include <Wire.h>  
#include "heltec.h" 

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=2) {
    Heltec.display->drawRect(i, i, DISPLAY_WIDTH-2*i, DISPLAY_HEIGHT-2*i);
    Heltec.display->display();
    delay(10);}
}

void loop() { }
