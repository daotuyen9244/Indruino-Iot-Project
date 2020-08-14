#include <WiFiManager.h>
#include <esp_wifi.h> 
#include <HTTPClient.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);
#else
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
WebServer server(80);
#endif
const char* www_username = "Indruino";
const char* www_password = "Indruino";
const char* serverweb    = "http://jsonplaceholder.typicode.com/";
String idget="1";
String mgspost;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  bool res;
  //wm.resetSettings(); //for test
  res = wm.autoConnect("AutoConnectAP","password"); // password protected apz
  if (wm.alreadyconnected())  wm.reboot();
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  ArduinoOTA.begin();
  server.begin();
  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
  server.on("/", [](){
  if(!server.authenticate(www_username, www_password))
      return server.requestAuthentication();
      menuwebsever();
  });
  server.on("/info",[](){
  siteinfo();
  });
  server.on("/diagnostic",[](){
  sitediagnostic();
  });
  server.on("/webcontrol",[](){
  webcontrol();
  });
  server.on("/webcontrol/get",[](){
  webcontrolget();
  });
  server.on("/webcontrol/post",[](){
  webcontrolpost();
  });
  
  
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
  if (server.hasArg("idget"))  idget=server.arg("idget");
}
void menuwebsever()
{
   String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +=".button { background-color: #4CAF50; border: none; color: white; padding: 24px 60px;";
   site +="text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
   site +=".button2 {background-color: #555555;}</style></head>";
   site +="<body>";
   site +="<h1>ESP32 Web Server</h1>";
   site +="<p><a href=\"/webcontrol\"><button class=\"button\">WEB CONTROL</button></a></p>";
   site +="<p><a href=\"/diagnostic\"><button class=\"button\">DIAGNOSTIC</button></a></p>";
   site +="<p><a href=\"/info\"><button class=\"button\">INFORMATION</button></a></p>";
   site +="</body></html>";
   server.send(200, "text/html",site);
  }
void siteinfo(){
  String isconnected=WiFi.isConnected()? "Yes":"No";
  String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +="</style></head><body>";
   site +="<h1>WIFI INFORMATION</h1>";
   site +="<p>---------------------------------------------------------------------</p>";
   site +="Access Point IP: " + WiFi.softAPIP().toString() + "<br/>";
   site +="Access Point MAC: " + (String)WiFi.softAPmacAddress() + "<br/>";
   site +="SSID: " + (String)WiFi.SSID() + "<br/>";
   site +="BSSID: " + (String)WiFi.BSSIDstr() + "<br/>";
   site +="Station IP: " + (String)WiFi.localIP() + "<br/>";
   site +="Station Gateway: " + (String)WiFi.gatewayIP() + "<br/>";
   site +="Station Subnet: " + (String)WiFi.subnetMask() + "<br/>";
   site +="DNS Server: " + (String)WiFi.dnsIP() + "<br/>";
   site +="Hostname: " + (String)WiFi.getHostname() + "<br/>";
   site +="Station MAC: " + WiFi.macAddress() + "<br/>";
   site +="Connected: " + isconnected + "<br/>";
   site +="<p>---------------------------------------------------------------------</p>";
   site +="</body></html>";
   server.send(200, "text/html",site);
  }
void sitediagnostic(){
  String isconnected=WiFi.isConnected()? "Yes":"No";
  String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +="</style></head><body>";
   site +="<h1>ESP32 INFORMATION</h1>";
   site +="<p>---------------------------------------------------------------------</p>";
   site +="Chip ID : " + String((uint32_t)ESP.getEfuseMac(),HEX) + "<br/>";
   site +="Chip Rev: " + (String)ESP.getChipRevision() + "<br/>";
   site +="Flash Size: " + (String)ESP.getFlashChipSize() + "<br/>";
   site +="Flash Speed: " + (String)ESP.getFlashChipSpeed() + "<br/>";
   site +="SDK Version: " + (String)esp_get_idf_version() + "<br/>";
   site +="CPU Frequency: " + (String)ESP.getCpuFreqMHz() + "MHz<br/>";
   site +="Sketch Size: " + (String)ESP.getSketchSize() + " bytes <br/>";
   site +="Sketch MD5 : " + ESP.getSketchMD5() + " <br/>";
   site +="Sketch Free Space : " + (String)ESP.getFreeSketchSpace() + " bytes <br/>";
   site +="Memory - Total Heap: " + (String)ESP.getHeapSize() + " bytes <br/>";
   site +="Memory - Free Heap: " + (String)ESP.getFreeHeap() + " bytes <br/>";
   site +="Memory - Lowest Level of Free Heap: " + (String)ESP.getMinFreeHeap() + "bytes <br/>";
   site +="Memory - Largest Level of Free Heap: " + (String)ESP.getMaxAllocHeap() + "bytes <br/>";
   site +="SPI RAM - Total: " + (String)ESP.getPsramSize() + " bytes <br/>";
   site +="SPI RAM - Free: " + (String)ESP.getFreePsram() + " bytes <br/>";
   site +="SPI RAM - Lowest: " + (String)ESP.getMinFreePsram() + " bytes <br/>";
   site +="SPI RAM - Largest: " + (String)ESP.getMaxAllocPsram() + " bytes <br/>";
   site +="<p>---------------------------------------------------------------------</p>";
   site +="</body></html>";
   server.send(200, "text/html",site);
  }
void webcontrol(){
  String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +=".button { background-color: #4CAF50; border: none; color: white; padding: 24px 60px;";
   site +="text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
   site +="</style></head><body>";
   site +="<h1>ESP32 GET/POST</h1>";
   site +="<p><a href=\"/webcontrol/get\"><button class=\"button\">&ensp;GET&ensp;</button></a>";
   site +="&emsp;&emsp;";
   site +="<a href=\"/webcontrol/post\"><button class=\"button\">&ensp;POST&ensp;</button></a></p>";
   site +="</body></html>";
   server.send(200, "text/html",site);
  }
void webcontrolget(){
    HTTPClient http;
    if (server.hasArg("idget"))  idget=server.arg("idget");
    String linkget=serverweb+(String)"comments?id="+idget;
    http.begin(linkget); //Specify the URL
    int httpCode = http.GET();                                        //Make the request
    String payload;
    if (httpCode > 0) { //Check for the returning code
        payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
        payload.replace(",","<br/>");
      }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end(); //Free the resources
  String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +=".button { background-color: #4CAF50; border: none; color: white; padding: 24px 60px;";
   site +="text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
   site +="</style></head><body>";
   site +="<h1>ESP32 GET/POST</h1>";
   site +="<p><a href=\"/webcontrol/get\"><button class=\"button\">&ensp;GET&ensp;</button></a>";
   site +="&emsp;&emsp;";
   site +="<a href=\"/webcontrol/post\"><button class=\"button\">&ensp;POST&ensp;</button></a></p>";
   site +="<h3>GET SERVER</h3>";
   site +="Get at website: "+linkget+"<br>";
   site +="<form action='/webcontrol/get' method='POST'>";
   site +="Get Post ID:<input type='text' name='idget' placeholder='your id get'><br>";
   site +="<input type='submit' value='Submit'></form><br/>";
   site +="<p><div style=\"border: 1px solid black\">"+payload+"</div></p>";
   site +="</body></html>";
   server.send(200, "text/html",site); 
  }
void webcontrolpost(){
  HTTPClient http;   
  String response;
  String linkpost=serverweb+(String)"posts";
  if (server.hasArg("postto"))  mgspost=server.arg("postto");
   http.begin(linkpost);  //Specify destination for HTTP request
   http.addHeader("Content-Type", "text/plain");             //Specify content-type header
   int httpResponseCode = http.POST(mgspost);   //Send the actual POST request
   if(httpResponseCode>0){  
    response = http.getString();                       //Get the response to the request
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
   }else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }
   http.end();  //Free resources
  String site ="<!DOCTYPE html><html>";
   site +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
   site +="<link rel=\"icon\" href=\"data:,\">";
   site +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
   site +=".button { background-color: #4CAF50; border: none; color: white; padding: 24px 60px;";
   site +="text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}";
   site +="</style></head><body>";
   site +="<h1>ESP32 GET/POST</h1>";
   site +="<p><a href=\"/webcontrol/get\"><button class=\"button\">&ensp;GET&ensp;</button></a>";
   site +="&emsp;&emsp;";
   site +="<a href=\"/webcontrol/post\"><button class=\"button\">&ensp;POST&ensp;</button></a></p>";
   site +="<h3>POST SERVER</h3>";
   site +="post at website: "+linkpost+"<br>";
   site +="<form action='/webcontrol/post' method='POST'>";
   site +="typing your post:<input type='text' name='postto' placeholder='writing something here'><br>";
   site +="<input type='submit' value='Submit'></form><br/>";
   site +="<p><div style=\"border: 1px solid black\"> Reponse Code: "+(String)httpResponseCode+"<br> Reponse ID:"+response+"<br/>message: "+mgspost+"</div></p>";
   site +="</body></html>";
   server.send(200, "text/html",site);
  }
