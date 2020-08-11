#include <Wire.h>
#include "heltec.h" 

String string = "Indruino";
float Float = 23.02;
bool Bool = 1;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display -> clear();
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,0,"String:");  
  Heltec.display->drawString(50,0,string);  
  Heltec.display->drawString(0,24,"Float:"); 
  Heltec.display->drawString(50,24,(String)Float); 
  Heltec.display->drawString(0,48,"Bool:"); 
  Heltec.display->drawString(50,48,(String)Bool); 
  Heltec.display->display();
}
  
void loop() {

}
