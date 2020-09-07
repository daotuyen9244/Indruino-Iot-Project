#include <ArduinoJson.h>
void setup() {

  Serial.begin(9600);
  Serial.println();

  String input = "{\"sensor\":\"gps\"}";

  DynamicJsonDocument doc(27);
  deserializeJson(doc, input);

  JsonObject obj = doc.as<JsonObject>();

  String sensor = obj["sensor"].as<String>();
  Serial.println("Sensor: " + sensor);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
