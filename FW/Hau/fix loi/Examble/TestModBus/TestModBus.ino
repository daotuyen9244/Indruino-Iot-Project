#include "SimpleModbusMaster_DUE.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Replace the next variables with your SSID/Password combination
const char* ssid = "J20";
const char* password = "!bakhanh!@!";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "45.77.45.244";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// LED Pin
const int ledPin = 25;

//////////////////// Port information ///////////////////
#define baud 9600 //baudrate
#define timeout 1000 //timeout 
#define polling 200 // the scan rate
#define retry_count 10 //count scan
#define TOTAL_NO_OF_REGISTERS 3 //so luong thanh ghi dung
// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.
enum
{
  PACKET1,
  PACKET2,
  //PACKET3,
  TOTAL_NO_OF_PACKETS // leave this last entry
};


Packet packets[TOTAL_NO_OF_PACKETS]; //Packet to confiured


unsigned int regs[TOTAL_NO_OF_REGISTERS]= {0}; // array buffer cho thanh ghi tai master

void setup()
{
  Serial.begin(9600);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  pinMode(ledPin, OUTPUT);

  // Initialize each packet
  //packet1 confiured with id slave =  1, function code Preset_multiple_register, addr of register =  0, count data = 2, array buffer address* = 0
  modbus_construct(&packets[PACKET1], 1, PRESET_MULTIPLE_REGISTERS, 0, 2, 0);

  //packet2 confiured with id slave = 2, function code force_single_coil, addr of coils = 0, count data =1, array buffer address* = 2;
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 0, 1, 2);

  // Initialize the Modbus Finite State Machine confiured modbus
  modbus_configure(&Serial, baud, timeout, polling, retry_count, packets, TOTAL_NO_OF_PACKETS, regs);
  
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // publish gói tin "Connected!" đến topic ESP8266/connection/board
      client.publish("DEMO", "Connected !");
      // Subscribe
      client.subscribe("DEMO");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void loop()
{
  modbus_update();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    regs[0]=50;
    //char tempString[8];
    char tempString[8]={"8t3"};
    client.publish("DEMO", tempString);
  }

  
  //regs[0]=6; //set data at holding Register addr 1
  //regs[1] = 5; //set data at holding Register addr 2
  //regs[2] = 0xFF00; // set data at coils addr 0 
  //coils ON = 0xFF00, coils OFF = 0x0000; 
  //update data to be written to arduino slave

//test with multiway
}
