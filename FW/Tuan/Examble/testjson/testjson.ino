#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "J20";
const char* password =  "!bakhanh!@!";
const char* mqttServer = "45.77.45.244";
const int mqttPort = 1883;
//const char* mqttUser = "yourInstanceUsername";
//const char* mqttPassword = "yourInstancePassword";
String id = "";
int data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
  Serial.println();

  client.setCallback(callback);
 
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

String messageTemp;
void decodeJson()
{
  DynamicJsonDocument doc(125);
  deserializeJson(doc, messageTemp);
  JsonObject obj = doc.as<JsonObject>();

  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230
  id = obj["code"].as<String>();
  data1 = obj["mNumSlv"].as<int>();
  data2 = obj["idSlv"].as<int>();
  data3 = obj["codeFunc"].as<int>();
  data4 = obj["A0"].as<int>();
  data5 = obj["A1"].as<int>();
  data6 = obj["A2"].as<int>();
  data7 = obj["A3"].as<int>();
  data8 = obj["A4"].as<int>();
  data9 = obj["A5"].as<int>();
  data10 = obj["A6"].as<int>();
  data11 = obj["A7"].as<int>();
  data12 = obj["IN_P"].as<int>();
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  decodeJson();

  Serial.println("id= " + id);
  Serial.println("mNumSlv= " + String(data1));
  Serial.println("idSlv= " + String(data2));
  Serial.println("codeFunc= "+ String(data3));
  Serial.println("A0= "+ String(data4));
  Serial.println("A1= "+ String(data5));
  Serial.println("A2= " + String(data6));
  Serial.println("A3= " + String(data7));
  Serial.println("A4= " + String(data8));
  Serial.println("A5= " + String(data9));
  Serial.println("A6= " + String(data10));
  Serial.println("A7= " + String(data11));
  Serial.println("IN_P= " + String(data12));
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // publish gói tin "Connected!" đến topic ESP8266/connection/board
      client.publish("/MASTER/POST/SENSOR", "Connected !");
      // Subscribe
      client.subscribe("/MASTER/POST/SENSOR");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}
 
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  StaticJsonDocument <512> doc;
  deserializeJson(doc, messageTemp);
  JsonObject obj = doc.as<JsonObject>();
  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230
  obj["code"] = "0+0";
  obj["mNumSlv"] = 0;
  obj["idSlv"] = 0;
  obj["codeFunc"] = 200;
  obj["A0"] = 230;
  obj["A1"] = 50;
  obj["A2"] = 36;
  obj["A3"] = 123;
  obj["A4"] = 30;
  obj["A5"] = 699;
  obj["A6"] = 2;
  obj["A7"] = 28;
  obj["IN_P"] = 120;
 
  char JSONmessageBuffer[200];
  serializeJson(obj, JSONmessageBuffer);
  //obj.to(JSONmessageBuffer, sizeof(JSONmessageBuffer));
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
