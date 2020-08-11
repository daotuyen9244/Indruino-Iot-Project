#include "DHT.h"
#include "heltec.h"     
        
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  
 
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin(); 

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_16);
}
 
void loop() {
  float doAm = dht.readHumidity();    
  float nhietDo = dht.readTemperature(); 
  Heltec.display->clear();
  Heltec.display->drawString(0,0,"t = ");
  Heltec.display->drawString(30,0,(String)nhietDo);
  Heltec.display->drawString(0,16,"h = ");
  Heltec.display->drawString(30,16,(String)doAm);
  Heltec.display->display();               
  delay(1000);                     
}
