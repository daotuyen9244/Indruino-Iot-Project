#include <Wire.h>
#include "heltec.h" 

const int button = 26;
int buttonStatus = 0;

void setup() {  
  pinMode(button, INPUT_PULLUP);  
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
}

void loop() {
  buttonStatus = digitalRead(button);
  if(buttonStatus == LOW){
    Heltec.display -> clear();
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0,0,"Button On");
    Heltec.display->display();
  }
  else{
    Heltec.display -> clear();
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0,0,"Button Off");
    Heltec.display->display();
  }
}
