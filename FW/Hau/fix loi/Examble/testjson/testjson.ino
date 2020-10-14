#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "modbus_function.h" //custom add function config
#include "indruino_data.h"

const char *ssid = "Trung Tam Nghien Cuu";
const char *password = "Indruino2020";
const char *mqttServer = "45.77.45.244";
const int mqttPort = 1883;

//data recive
String code = "";
volatile byte mNumSlv;
volatile uint16_t idSlv;
volatile byte codeFunc;
volatile uint16_t _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7;
volatile byte OUT_P;
//data recive

Indruino indurino;
WiFiClient espClient;
PubSubClient client(espClient);

String data_receive = "";
//modbus
CONVERT cv_data;
CV_ convert_data2byte;
void sync_starup();
void setup_wifi();
void setup_mqtt();
void setup_modbus();
void setup_connect(); //mqtt, wifi,....
void callback(char *topic, byte *message, unsigned int length)
{
  String _topic = String(topic);
  //  Serial.println(topic);
  if (_topic == "/MASTER/GET/SENSOR")
  {
    for (uint16_t i = 0; i < length; i++)
    {
      data_receive += (char)message[i];
    }
    //   Serial.println(data_receive);
    decode();
    //  Serial.println(String(OUT_P));
    data_receive = "";
  }
}

void setup()
{
  indurino.init();
  cv_data._uintAr = au16data;

  setup_connect();

}
unsigned long time_last1 = 0;
unsigned long time_last2 = 0;
unsigned long time_last3 = 0;
unsigned long time_count = 0;
byte last_valueINP = 0x00;
uint16_t last_valueADC0 = 0;
void loop()
{
#if 1
  if (millis() - time_last3 > 1000)
  {
    getValue_ADC();
    getValue_INP();
    time_last3 = millis();
  }

  if (ram.readUShort(Ram_ADC0) != last_valueADC0)
  {
    //if (millis() - time_last1 > 500)
    {
      encode_data4sensor_s();
      last_valueADC0 = ram.readUShort(Ram_ADC0);
      time_last1 = millis();
    }
  }

  if (ram.readByte(Ram_IN_P) != last_valueINP)
  {
    //if (millis() - time_last2 > 500)
    {
      encode_data4sensor_s();
      last_valueINP = ram.readByte(Ram_IN_P);
      time_last2 = millis();
    }
  }

#endif
  
  client.loop(); //keep alive
}

uint16_t tmp_value = 0;
uint16_t count_ram = 0;
void getValue_INP()
{
  uint8_t result = modbus.readByte_modbus(Ram_IN_P);
  ram.writeByte(Ram_IN_P, result);
  //  ram.writeUShort(Ram_IN_P/2, node.getResponseBuffer(0));
}

void getValue_ADC()
{
  au16data[Ram_ADC0] = modbus.readUShort_modbus(Ram_ADC0);
  au16data[Ram_ADC1] = modbus.readUShort_modbus(Ram_ADC1);
  au16data[Ram_ADC2] = modbus.readUShort_modbus(Ram_ADC2);
  au16data[Ram_ADC3] = modbus.readUShort_modbus(Ram_ADC3);

  ram.writeUShort(Ram_ADC0, cv_data._uintAr[Ram_ADC0]); //write to ram
  ram.writeUShort(Ram_ADC1, cv_data._uintAr[Ram_ADC1]);
  ram.writeUShort(Ram_ADC2, cv_data._uintAr[Ram_ADC2]);
  ram.writeUShort(Ram_ADC3, cv_data._uintAr[Ram_ADC3]);
}
void getValue_OUTP()
{
  uint8_t result = modbus.readByte_modbus(Ram_OUT_P);
  ram.writeByte(Ram_OUT_P, result);
}
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
  obj["A0"] = ram.readUShort(Ram_ADC0); //ram.readUShort(Ram_ADC0);
  obj["A1"] = ram.readUShort(Ram_ADC1);
  obj["A2"] = ram.readUShort(Ram_ADC2);
  obj["A3"] = ram.readUShort(Ram_ADC3);
  obj["A4"] = ram.readUShort(Ram_ADC4);
  obj["A5"] = ram.readUShort(Ram_ADC5);
  obj["A6"] = ram.readUShort(Ram_ADC6);
  obj["A7"] = ram.readUShort(Ram_ADC7);
  obj["IN_P"] = ram.readByte(Ram_IN_P);

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
//void getValue_time_packet
byte last_out_P = 0x00;
void decode() //send data
{
  DynamicJsonDocument doc(512);
  deserializeJson(doc, data_receive);
  //"code":"0+0","mNumSlv"":0, "idSlv":0,"codeFunc":200,"A0":213,"A1":150,"A2":360,"A3":1000,"A4":30,"A5":999,"A6":69,"A7":23,"IN_P":230

  code = doc["code"].as<String>();
  mNumSlv = doc["mNumSlv"].as<byte>();
  idSlv = doc["idSlv"].as<uint16_t>();
  codeFunc = doc["codeFunc"].as<byte>();
  _A0 = doc["A0"].as<uint16_t>(); //read
  _A1 = doc["A1"].as<uint16_t>(); //read
  _A2 = doc["A2"].as<uint16_t>(); //read
  _A3 = doc["A3"].as<uint16_t>(); //read
  _A4 = doc["A4"].as<uint16_t>(); //set
  _A5 = doc["A5"].as<uint16_t>(); //set
  _A6 = doc["A6"].as<uint16_t>(); //set
  _A7 = doc["A7"].as<uint16_t>(); //set
  OUT_P = doc["OUT_P"].as<uint8_t>();

  au16data[Ram_ADC4] = modbus.readUShort_modbus(Ram_ADC4);

  au16data[Ram_ADC5] = modbus.readUShort_modbus(Ram_ADC5);

  au16data[Ram_ADC6] = modbus.readUShort_modbus(Ram_ADC6);

  au16data[Ram_ADC7] = modbus.readUShort_modbus(Ram_ADC7);

  convert_data2byte.value = _A4;
  ram.writeUShort(Ram_ADC4, _A4);
  ram.writeUShort(Ram_ADC5, _A5);
  ram.writeUShort(Ram_ADC6, _A6);
  ram.writeUShort(Ram_ADC7, _A7);
  //convert_data2byte.value = _A5;
  modbus.writeUShort_modbus(Ram_ADC4, ram.readUShort(Ram_ADC4));
  if (OUT_P != last_out_P)
  {
    last_out_P = OUT_P;
    cv_data._byteAr[Ram_OUT_P] = OUT_P;
    modbus.writeByte_modbus(Ram_OUT_P, OUT_P);
  }

  //writeData();

  //  byte *ptr_value = (byte*)hreg;
  // ptr_value[2] = OUT_P;
  //myRam.writeByte(5, OUT_P);
  //write to register modbus

  //write to register modbus
}

//chua test
void writeData()
{
  for (uint16_t count = 0; count < sizeRegs; count++)
  {
    modbus.writeSingleRegister(0, au16data[count]);
  }
}
//chua test

void sync_starup()
{
  modbus.readData(); //dong bo du lieu
  encode_data4sensor_s();
  decode();
}

void setup_wifi()
{
  WiFi.begin(ssid, password);
  //Wifi_connect
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    // Serial.println("Connecting to WiFi..");
  }
}
void setup_mqtt()
{
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
}
void setup_modbus()
{
  Serial.begin(9600);
  modbus.init(1, 9600, Serial);
  sync_starup();
}
void setup_connect()
{
  setup_wifi();
  setup_mqtt();
  setup_modbus();
}