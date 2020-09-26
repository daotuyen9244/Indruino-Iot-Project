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
String user;
String password;
String ssid;
String pass;
String server;
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
    ssid="";
    for (int i=Rom_WiFI_User; i<Rom_WiFi_Mac; i++)
    {
      ssid += char(indruino.myRom()->readChar(i));
    }
    Serial.print("SSID: ");
    Serial.println(ssid);

    pass = "";
    for (int i=Rom_WiFi_Pass; i<Rom_mPrtcol; i++)
    {
      pass += char(indruino.myRom()->readChar(i));
    }
    Serial.print("PASSWORD: ");
    Serial.println(pass);

    server ="";
    server = String(indruino.myRom()->readByte(Rom_mqtt_server)) +"."+ String(indruino.myRom()->readByte(Rom_mqtt_server+1)) +"."+ String(indruino.myRom()->readByte(Rom_mqtt_server+2)) +"."+ String(indruino.myRom()->readByte(Rom_mqtt_server+3));    
    Serial.print("mqtt server: ");
    Serial.println(server);

    Serial.print("mqtt port: ");
    Serial.println(indruino.myRom()->readUShort(Rom_mqtt_port));
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
  mqttClient.setServer(server.c_str(),indruino.myRom()->readShort(Rom_mqtt_port));
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
  Serial.println("Clear EEPROM!");
  clear_data();
  
  ssid =webServer.arg("ssid");
  for (int i = 0; i < ssid.length(); i++) 
  {
    indruino.myRom()->writeChar(Rom_WiFI_User+i, ssid[i] );
  }

  pass = webServer.arg("pass");
  for (int i = 0; i < pass.length(); i++) 
  {
    indruino.myRom()->writeChar(Rom_WiFi_Pass+i, pass[i] );
  }
  int id1, id2, id3, id4;
  sscanf((webServer.arg("server")).c_str(), "%d.%d.%d.%d", &id1, &id2,&id3, &id4);
  indruino.myRom()->writeByte(Rom_mqtt_server,id1);
  indruino.myRom()->writeByte(Rom_mqtt_server+1,id2);
  indruino.myRom()->writeByte(Rom_mqtt_server+2,id3);
  indruino.myRom()->writeByte(Rom_mqtt_server+3,id4);
  
  indruino.myRom()->writeShort(Rom_mqtt_port, (webServer.arg("port")).toInt());
 
  Serial.println("Writed to EEPROM!");
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
  for (int i=Rom_WiFI_User; i<Rom_WiFi_Mac; i++)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=Rom_WiFi_Pass; i<Rom_mPrtcol; i++)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=Rom_mqtt_server; i<Rom_mqtt_user; i++)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
  for (int i=Rom_mqtt_port; i<Rom_mqtt_topic_lwt; i++)
  {
    indruino.myRom()->writeByte(i, 0);   
  }
}
