#include "heltec.h" 
#include <Wire.h>

#define ADDRESS 0x5A
// RAM
#define ADDRESS_1 0x04
#define ADDRESS_2 0x05
#define ADDRESS_3 0x06
#define ADDRESS_4 0x07
#define ADDRESS_5 0x08

uint16_t DATA;

void setup() {
Serial.begin(115200);
pinMode(Vext,OUTPUT);
digitalWrite(Vext,LOW);                           //set vext to LOW
delay(500);                                       //just to make sure the sensor has powered up

Wire.begin();
Wire.beginTransmission((uint8_t)ADDRESS);         // start transmission to device
Wire.write((uint8_t)ADDRESS_4);                   // sends register address to read from
Wire.endTransmission();
Wire.requestFrom((uint8_t)ADDRESS, 3);            // send data n-bytes read
DATA = Wire.read();                               // receive DATA
DATA |= Wire.read() << 8;                         // receive DATA
Serial.println(DATA, HEX);

Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
Heltec.display->init();
Heltec.display->flipScreenVertically();
Heltec.display->setFont(ArialMT_Plain_16);
Heltec.display->drawString(0,0,"Read I2C:");
String string_ADDRESS =  String(ADDRESS, HEX);    // Convert ADDRESS hex to string
Heltec.display->drawString(100,0,string_ADDRESS);
Heltec.display->drawString(0,24,"Data: ");  
String string_DATA =  String(DATA, HEX);          // Convert DATA hex to string  
Heltec.display->drawString(100,24,string_DATA);  
Heltec.display->display();
}

void loop() {
}
