#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

const char* ssid = "TDT";
const char* password = "TDTguest01";
const char* mqtt_server = "45.77.254.67";
const char* mqtt_username = "indruino";
const char* mqtt_password = "indruino";
#define led 25

WiFiClient espClient;
PubSubClient client(espClient);

String input = "";

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
    input+=(char)payload[i];
  }
  Serial.println(input);
  decodeJson();
  input ="";
}
void decodeJson()
{
  DynamicJsonDocument doc(50);
  deserializeJson(doc, input);
  JsonObject obj = doc.as<JsonObject>();

  boolean led_state = obj["led"].as<boolean>();

  Serial.println(led_state);

  if(led_state)
  {
    digitalWrite(led, 1);
  }
  else
  {
    digitalWrite(led, 0);
  }
}
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
          //o day minh dung lwt de kiem tra trang thai realtime cua client, xem xet xem client nay offline hay online
          //neu online thi khi cac client khac subscribe vao topic "die" thi ngay lap tuc se nhan duoc payload "1"
          //neu offline thi khi cac client khac subscribe vao topic "die" thi ngay lap tuc nhan duoc payload "0"
          //do o day minh set cờ returned tai lwt la true
          //neu client die thi broker se gui payload cua lwt vao topic tuong ung
          client.subscribe("led", 1);
        }
        else
        {
          delay(5000);
        }
      }
    }
 client.loop(); 
}
