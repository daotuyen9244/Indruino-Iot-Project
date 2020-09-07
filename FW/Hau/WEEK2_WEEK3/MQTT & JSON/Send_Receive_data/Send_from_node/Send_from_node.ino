#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "TDT";
const char* password = "TDTguest01";
const char* mqtt_server = "45.77.254.67";
const char* mqtt_username = "indruino";
const char* mqtt_password = "indruino";

const char* id = "01";
float data1 = 0.1;
int data2 = 1;
bool data3 = true;
String data4 = "mot";


WiFiClient espClient;
PubSubClient client(espClient);

String output = "";
void encodeJson()
{
  DynamicJsonDocument doc(125);
  JsonObject obj = doc.to<JsonObject>();
  obj["id"] = id;
  obj["data1"] = data1;
  obj["data2"] = data2;
  obj["data3"] = data3;
  obj["data4"] = data4;
  
  serializeJson(doc, output);
  Serial.println(output);
}
void setup_wifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected");
}

void callback(char *topic, byte*payload, unsigned int length)
{
  for(int i = 0;i < length; i++)
  {
  
  }

}
void setup() {

  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  encodeJson(); //ma hoa du lieu thanh Json
}

void loop() {

    if(!client.connected())
    {
      while(!client.connected())
      {
        //client id, tao client name ESP32_test, lwt: topic: "die", payload "0", returned: true, qos 1, username, password mqtt
        if(client.connect("ESP32_test", mqtt_username, mqtt_password,"die", MQTTQOS0, 1, "0"))
        {
          client.publish("die", "1", 1);
     
          client.publish("data", output.c_str()); //send output to topic data
        }
        else
        {
          delay(5000);
        }
      }
    }
 client.loop(); 
}
