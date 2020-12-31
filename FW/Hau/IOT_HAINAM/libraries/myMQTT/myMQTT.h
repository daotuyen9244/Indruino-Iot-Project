#ifndef MYMQTT_H
#define MYMQTT_H
#include <Arduino.h>
#include "indruino_data.h"
#include "modbus_function.h"
#include "config_mem.h"
#include "WiFi_Setup.h"
#include <ArduinoJson.h>

const char *mqttServer = "45.77.45.244";
const int mqttPort = 1883;

//data recive
// //data recive
String code = "";
String data_receive = "";
volatile byte mNumSlv;
volatile uint16_t idSlv;
volatile byte codeFunc;
volatile uint16_t _A0, _A1, _A2, _A3, _A4, _A5, _A6, _A7;
volatile byte OUT_P;
//data recive
//data recive



WiFiClient espClient;
PubSubClient client(espClient);

void encode_data4sensor_s_mqtt() //send data
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

byte last_out_P = 0x00;


void decode_mqtt() //send data
{
  DynamicJsonDocument doc(512);
  deserializeJson(doc,data_receive);
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

  au16data[Ram_ADC0] = modbus.readUShort_modbus(Ram_ADC0);

  au16data[Ram_ADC1] = modbus.readUShort_modbus(Ram_ADC1);

  au16data[Ram_ADC2] = modbus.readUShort_modbus(Ram_ADC2);

  au16data[Ram_ADC3] = modbus.readUShort_modbus(Ram_ADC3);

  convert_data2byte.value = _A4;
  ram.writeUShort(Ram_ADC4, _A4);
  ram.writeUShort(Ram_ADC5, _A5);
  ram.writeUShort(Ram_ADC6, _A6);
  ram.writeUShort(Ram_ADC7, _A7);
  //convert_data2byte.value = _A5;
  modbus.writeUShort_modbus(Ram_ADC4, _A4);
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
       //Serial.println(data_receive);
     decode_mqtt();
    //  Serial.println(String(OUT_P));
     data_receive = "";
  }
}
void setup_mqtt() //setup mqttServer, mqttPort
{
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  //
  while (!client.connected())
  {
    if (client.connect("ESP32Client"))
    {
      client.subscribe("/MASTER/GET/SENSOR");
    }
    else
    {
      delay(2000);
    }
  }
}
#endif