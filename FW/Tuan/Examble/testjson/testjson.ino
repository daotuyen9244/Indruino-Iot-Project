#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Iphone";
const char* password =  "tuan2302";
const char* mqttServer = "45.77.45.244";
const int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  Serial.println();
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    //if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } 
    else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
 
}
 
void loop() {
 
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230
  JSONencoder["code"] = "0+0";
  JSONencoder["mNumSlv"] = 0;
  JSONencoder["idSlv"] = 0;
  JSONencoder["codeFunc"] = 200;
  JSONencoder["A0"] = 213;
  JSONencoder["A1"] = 150;
  JSONencoder["A2"] = 360;
  JSONencoder["A3"] = 1000;
  JSONencoder["A4"] = 30;
  JSONencoder["A5"] = 999;
  JSONencoder["A6"] = 69;
  JSONencoder["A7"] = 23;
  JSONencoder["IN_P"] = 230;
 
  char JSONmessageBuffer[200];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);
 
  if (client.publish("/MASTER/POST/SENSOR", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }
 
  client.loop();
  Serial.println("-------------");
 
  delay(10000);
 
}
