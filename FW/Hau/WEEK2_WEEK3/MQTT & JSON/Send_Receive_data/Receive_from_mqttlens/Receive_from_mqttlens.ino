#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "TDT";
const char* password = "TDTguest01";
const char* mqtt_server = "45.77.254.67";
const char* mqtt_username = "indruino";
const char* mqtt_password = "indruino";

String id = "";
float data1;
int data2;
bool data3;
String data4="";


WiFiClient espClient;
PubSubClient client(espClient);

String output = "";
void decodeJson()
{
  DynamicJsonDocument doc(125);
  deserializeJson(doc, output);
  
  id = doc["id"].as<String>();
  data1 = doc["data1"].as<float>();
  data2 = doc["data2"].as<int>();
  data3 = doc["data3"].as<boolean>();
  data4 = doc["data4"].as<String>();
}
void setup_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
}

void callback(char *topic, byte*payload, unsigned int length)
{
  for (int i = 0; i < length; i++)
  {
    output+=(char)payload[i];
  }
  Serial.println(output);
  decodeJson();

  Serial.println("id= " + id);
  Serial.println("data1= " + String(data1));
  Serial.println("data2= "+ String(data2));
  Serial.println("data3= "+ String(data3));
  Serial.println("data4= "+ data4);
  


  output="";

}
void setup() {

  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected())
  {
    while (!client.connected())
    {
      //client id, tao client name ESP32_test, lwt: topic: "die", payload "0", returned: true, qos 1, username, password mqtt
      if (client.connect("ESP32_test", mqtt_username, mqtt_password, "die", MQTTQOS0, 1, "0"))
      {
        client.publish("die", "1", 1);

        client.subscribe("data", 1);
      }
      else
      {
        delay(5000);
      }
    }
  }
  client.loop();
}
