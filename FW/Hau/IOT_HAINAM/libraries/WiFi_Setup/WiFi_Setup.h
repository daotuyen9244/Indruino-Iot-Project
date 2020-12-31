#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>

const char *ssid = "Trung Tam Nghien Cuu";
const char *password = "Indruino2020";


void setup_wifi()
{
  WiFi.begin(ssid, password);
  //Wifi_connect
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    // Serial.prinaratln("Connecting to WiFi..");
  }
}


#endif //WIFI_SETUP_H