#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "SimpleModbusMaster_DUE.h"

#include "ModbusRtu.h"
#include "indruino_data.h"

const char *ssid = "Indruino_Student";
const char *password = "Indruino2019";
const char *mqttServer = "45.77.45.244";
const int mqttPort = 1883;

Modbus master(0, 0);

modbus_t telegram[10];

unsigned long u32wait;
unsigned long value;


#define baud 9600      //baudrate
#define timeout 5000   //timeout
#define polling 300   // the scan rate
#define retry_count 10 //count scan
#define TOTAL_NO_OF_REGISTERS 1

//data recive
String code = "";
volatile byte mNumSlv;
volatile uint16_t idSlv;
volatile byte codeFunc;
volatile uint16_t _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7;
volatile byte OUT_P;
//data recive

Indruino indurino;

// enum
// {
//   PACKET1,
//   PACKET2,
//   //PACKET3,
//   TOTAL_NO_OF_PACKETS // leave this last entry
// };
// Packet packets[TOTAL_NO_OF_PACKETS]; //Packet to confiured

uint16_t *regs = nullptr;

WiFiClient espClient;
PubSubClient client(espClient);

String data_receive = "";

SRAM myRam;
//modbus


void callback(char *topic, byte *message, unsigned int length)
{
  String _topic = String(topic);
//  Serial.println(topic);
  if (_topic == "/MASTER/GET/SENSOR")
  {
    for(uint16_t i =0; i< length; i++)
    {
      data_receive+=(char)message[i];
    }
 //   Serial.println(data_receive);
    decode();
  //  Serial.println(String(OUT_P));
    data_receive = "";
  }
}

 typedef union convert
{
  byte *_byteAr;
  uint16_t*_uintAr;
} CONVERT;

CONVERT cv_data;
uint8_t u8state = 0;
uint8_t u8query = 0;
void setup()
{

  indurino.init();
  regs = (uint16_t*)indurino.myRam()->array(0); //setup ram for modbus
  cv_data._uintAr = regs;
  //Serial.begin(115200);
  //Serial.println();

  //modbus_construct(&packets[PACKET1], 1, PRESET_MULTIPLE_REGISTERS, 0, 100, 0);
  //modbus_configure(&Serial, baud, timeout, polling, retry_count, 7 ,packets, TOTAL_NO_OF_PACKETS, regs);

  WiFi.begin(ssid, password);
  //Wifi_connect
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
   // Serial.println("Connecting to WiFi..");
  }
//  Serial.println("Connected to the WiFi network");
  //Wifi_connect
  //
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  //
  while (!client.connected())
  {
  
  //  Serial.println("Connecting to MQTT...");

    //if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
    if (client.connect("ESP32Client"))
    {
      client.subscribe("/MASTER/GET/SENSOR");
  //    Serial.println("connected");
    }
    else
    {
 //     Serial.print("failed with state ");
 //     Serial.print(client.state());
      delay(2000);
    }
  }

//read
  telegram[0].u8id = 1;
  telegram[0].u8fct= 3;
  telegram[0].u16CoilsNo = 100;
  telegram[0].u16RegAdd = 0;
  telegram[0].au16reg = regs;
//read
  telegram[1].u8id = 1;
  telegram[1].u8fct = 6;
  telegram[1].u16CoilsNo=1;
  telegram[1].u16RegAdd= 14;
  telegram[1].au16reg = regs+14;

  master.begin(9600);
  master.setTimeOut(1000);
  
}
unsigned long time_last = 0;
void loop()
{
  //modbus_update();
  
  switch (u8state)
  {
  case 0:
    if (millis() > u32wait)
      u8state++; // wait state
    break;
  case 1:
    master.query(telegram[1]); // send query (only once)
  case 2:
     // check incoming messages
     master.poll();
    if (master.getState() == COM_IDLE)
    {
      u8state = 0;
      u32wait = millis() + 1000;
    }
    break;
  }

  if (millis() - time_last > 1000)
  {
    encode_data4sensor_s();
    time_last = millis();
  }
   client.loop();
}


uint16_t tmp_value = 0;
void encode_data4sensor_s() //send data
{

  ////
  DynamicJsonDocument doc(512);
  JsonObject obj = doc.to<JsonObject>();
  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230
  obj["code"] = "0+0";
  obj["mNumSlv"] = 0;
  obj["idSlv"] = 0;
  obj["codeFunc"] = 200;
  obj["A0"] = tmp_value++;
  obj["A1"] = 150;
  obj["A2"] = 360;
  obj["A3"] = 1000;
  obj["A4"] = 30;
  obj["A5"] = 999;
  obj["A6"] = 69;
  obj["A7"] = 23;
  obj["IN_P"] = 230;

  String output = "";

  serializeJson(doc, output);
  // Serial.println(output);
  if (client.publish("/MASTER/POST/SENSOR", output.c_str()) == true)
  {
    //Serial.println("Success sending message");
  }
  else
  {
    //Serial.println("Error sending message");
  }
}



void decode() //send data
{
  DynamicJsonDocument doc(512);
  deserializeJson(doc, data_receive);
  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230

  code = doc["code"].as<String>();
  mNumSlv = doc["mNumSlv"].as<byte>();
  idSlv = doc["idSlv"].as<uint16_t>();
  codeFunc = doc["codeFunc"].as<byte>();
  _A0 = doc["A0"].as<uint16_t>();
  _A1 = doc["A1"].as<uint16_t>();
  _A2 = doc["A2"].as<uint16_t>();
  _A3 = doc["A3"].as<uint16_t>();
  _A4 = doc["A4"].as<uint16_t>();
  _A5 = doc["A5"].as<uint16_t>();
  _A6 = doc["A6"].as<uint16_t>();
  _A7 = doc["A7"].as<uint16_t>();
  OUT_P = doc["OUT_P"].as<byte>();

  cv_data._byteAr[Ram_OUT_P] = OUT_P;
  master.query(telegram[1]);
//  byte *ptr_value = (byte*)hreg;
 // ptr_value[2] = OUT_P;
  //myRam.writeByte(5, OUT_P);
  //write to register modbus

  //write to register modbus
}
