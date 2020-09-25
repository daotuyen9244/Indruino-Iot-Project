#include <WiFi.h>
#include <WebServer.h>
#include "indruino_data.h"
#include <PubSubClient.h>
#include <Wire.h>
#include "index.h"

WebServer webServer(80);
WiFiClient   wifiClient;
PubSubClient mqttClient(wifiClient);
Indruino indruino;

char* ssid_ap = "ESP32_AP";
char* pass_ap = "12345678";
String ssid;
String pass;
String server;
String port;
void setup() 
{
  Serial.begin(115200);
  indruino.init();
  delay(10);
  if(read_EEPROM())
  {
    checkConnection();
  }
  else
  {
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap,pass_ap);
    Serial.println("Soft Access Point mode!");
    Serial.print("Please connect to ");
    Serial.println(ssid_ap);
    Serial.print("Web Server IP Address: ");
    IPAddress IP = WiFi.softAPIP();
    Serial.println(IP);
  }
  webServer.on("/",mainpage);
  webServer.on("/getIP",get_IP);
  webServer.on("/writeEEPROM",write_EEPROM);
  webServer.on("/restartESP",restart_ESP);
  webServer.on("/clearEEPROM",clear_EEPROM);
  webServer.begin();
}
void loop()
{
  webServer.handleClient();
}
//==========Chương trình con=================//
void mainpage()
{
  String s = FPSTR(MainPage);
  webServer.send(200,"text/html",s);
}
void get_IP()
{
  String s = WiFi.localIP().toString();
  webServer.send(200,"text/html", s);
}
boolean read_EEPROM()
{
  Serial.println("Reading EEPROM...");
  if(indruino.myRom()->readChar(21)!=0)
  {
    ssid = "";
    pass = "";
    server ="";
    port ="";
    for (int i=WiFI_User; i<WiFi_Mac; ++i)
    {
      ssid += char(indruino.myRom()->readChar(i));
    }
    Serial.print("SSID: ");
    Serial.println(ssid);
    for (int i=WiFi_Pass; i<mPrtcol; ++i)
    {
      pass += char(indruino.myRom()->readChar(i));
    }
    Serial.print("PASSWORD: ");
    Serial.println(pass);

    for (int i=mqtt_server; i<mqtt_user; ++i)
    {
      server += char(indruino.myRom()->readChar(i));
    }
    Serial.print("mqtt server: ");
    Serial.println(server);

    for (int i=mqtt_port; i<mqtt_topic_lwt; ++i)
    {
      port += char(indruino.myRom()->readChar(i));
    }
    Serial.print("mqtt port: ");
    Serial.println(port);
    return true;
  }
  else
  {
    Serial.println("Data wifi not found!");
    return false;
  }
}
//---------------SETUP WIFI------------------------------
void checkConnection() 
{
  Serial.println();
  Serial.print("Check connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.begin(ssid.c_str(),pass.c_str());
  mqttClient.setServer(server.c_str(), port.toInt());
  int count=0;
  while(count < 50)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      WiFi.mode(WIFI_STA);
      Serial.println();
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("Web Server IP Address: ");
      Serial.println(WiFi.localIP());
      if (mqttClient.connect("ESP32Client")) 
      {
        Serial.println("Connected");
      }
      else 
      {
        Serial.println("Connection failed:" + String(mqttClient.state()));
      }
      return;
    }
    delay(200);
    Serial.print(".");
    count++;
  }
  Serial.println("Timed out.");
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_ap,pass_ap);
  Serial.println("Soft Access Point mode!");
  Serial.print("Please connect to ");
  Serial.println(ssid_ap);
  Serial.print("Web Server IP Address: ");
  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
}
void write_EEPROM()
{
  ssid = webServer.arg("ssid");
  pass = webServer.arg("pass");
  server = webServer.arg("server");
  port = webServer.arg("port");
  Serial.println("Clear EEPROM!");
  clear_data();
  for (int i = 0; i < ssid.length(); ++i) 
  {
    indruino.myRom()->writeChar(WiFI_User+i, ssid[i] );
  }
  for (int i = 0; i < pass.length(); ++i) 
  {
    indruino.myRom()->writeChar(WiFi_Pass+i, pass[i] );
  }

  for (int i = 0; i < server.length(); ++i) 
  {
    indruino.myRom()->writeChar(mqtt_server+i, server[i] );
  }

  for (int i = 0; i < port.length(); ++i) 
  {
    indruino.myRom()->writeChar(mqtt_port+i, port[i] );
  } 
  Serial.println("Writed to EEPROM!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("PASS: ");
  Serial.println(pass);
  Serial.println(server);
  Serial.println(port);
  String s = "Đã lưu thông tin";
  webServer.send(200, "text/html", s);
}
void restart_ESP()
{
  ESP.restart();
  String s = "Đã khởi động lại ESP32";
  webServer.send(200, "text/html", s);
}
void clear_EEPROM()
{
  Serial.println("Clear EEPROM!");
  clear_data();
  String s = "Đã xóa data";
  webServer.send(200,"text/html", s);
}

void clear_data()
{
  for (int i=WiFI_User; i<WiFi_Mac; ++i)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=WiFi_Pass; i<mPrtcol; ++i)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=mqtt_server; i<mqtt_user; ++i)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=mqtt_port; i<mqtt_topic_lwt; ++i)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
}
