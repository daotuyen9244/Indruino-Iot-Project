#include <Wire.h> 
#include <WiFi.h> 
#include "heltec.h" 

const char* ssid     = "Indruino_Student";
const char* password = "Indruino2019";

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();

  WiFi.begin(ssid, password);
  delay(10);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Print local IP address and start web server
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "WiFi connected.");
  Heltec.display->drawString(0, 15, "IP address: ");
  Heltec.display->drawString(0, 30, WiFi.localIP().toString());
  Serial.println(WiFi.localIP());
  Heltec.display->display();
  delay(2000);
  Heltec.display->clear();
}

void loop() { }
