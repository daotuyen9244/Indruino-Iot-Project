
#include <WiFi.h>
#include <WiFiClient.h>



void setup() {
  Serial.begin(9600);
  while(!Serial);
  WiFi.begin("TruongHau2.4", "26309224");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());
}

unsigned long lastSentTime = 0;

void loop() {
  

}
