#include "ArduinoJson.h"
 
void setup() {
 
  Serial.begin(115200);
  Serial.println();
 
}
 
void loop() {
 
  Serial.println("Parsing start: ");
 
  char JSONMessage[] = " {"code":"0+0","mNumSlv":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230}"; //Original message
 
  StaticJsonBuffer<300> JSONBuffer;                         //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(JSONMessage); //Parse message
 
  if (!parsed.success()) {   //Check for errors in parsing
 
    Serial.println("Parsing failed");
    delay(5000);
    return;
 
  }
 
  const char * codeBoard = parsed["code"]; 
  char valueCode = parsed["0+0"];
  const char * mNumSlv = parsed["mNumSlv"];
  int valueSlv = parsed[0];

 
  Serial.print("codeBoard: ");
  Serial.println(valueCode);
  Serial.print("mNumSlv ");
  Serial.println(valueSlv);
 
  Serial.println();
  delay(5000);
 
}
