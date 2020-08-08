#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "heltec.h"

Adafruit_BMP085 bmp;  

void setup() {
  
  Serial.begin(115200);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
}  
void loop() {  
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");    
    Serial.println();
    
    Heltec.display->clear();
    Heltec.display->drawString(0,0,"Temperature = ");
    Heltec.display->drawString(0,70,(String)bmp.readTemperature());
    Heltec.display->drawString(0,30,"Pressure      = ");
    Heltec.display->drawString(10,70,(String)bmp.readPressure());
    Heltec.display->display();
    delay(1000);
}
