#include "heltec.h"

const int SensorPin = 17; 
const int LedPin = 14;
int sensor_status = 0;

void setup() {
  pinMode (SensorPin, INPUT);
  pinMode (LedPin, OUTPUT);  
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_16);
}

void loop() {
  sensor_status = digitalRead(SensorPin);
  
  if(sensor_status == LOW){
      Heltec.display->clear();
      Heltec.display->drawString(0,0,"Sensor On");
      Heltec.display->display();
      digitalWrite(LedPin, HIGH);
    }
   else{
      Heltec.display->clear();
      Heltec.display->drawString(0,0,"Sensor Off");
      Heltec.display->display();
      digitalWrite(LedPin, LOW); 
    }
}
