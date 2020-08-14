#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "Trung Tam Nghien Cuu";
const char* password = "Indruino2020";
const int led = 25;
String formattedTime;

WebServer server(80); 
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Set LED on
void LEDON() {
  digitalWrite(led,HIGH);  
  server.sendHeader("Location","/");    
  server.send(303);                     
}

// Set LED off
void LEDOFF() {
  digitalWrite(led,LOW);  
  server.sendHeader("Location","/");    
  server.send(303);                     
}

void handleSend(){
      String text1 = server.arg("dataf");
      String text2 = server.arg("datas");
      String text3 = server.arg("datat");
      Serial.println(text1+text2+text3);
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.send(301);
}

void handleLogin() {
  String msg;
  if (server.hasArg("DISCONNECT")) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  if (server.hasArg("uname") && server.hasArg("pass")) {
    if (server.arg("uname") == "IndruinoStudent" &&  server.arg("pass") == "Indruino2019") {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      //server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      return;
    }
    msg = "Sai tên đăng nhập hoặc mật khẩu. Hãy thử lại!.";
  }
  String content = "<!DOCTYPE html><html>";
  content += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  content += "<link rel='icon\' href='data:,\'>";
  content += "<title>Control Led</title><meta charset='utf-8'></head>";
  content += "<body><center><H1>CONTROL LED</H1>";
  content += "<form action='/login' method='POST'>"; 
  content += "<label for='uname'>User: &nbsp &nbsp &nbsp &nbsp &nbsp</label>";
  content += "<input type='text' id='uname' name='uname' placeholder='user name'><br><br>";
  content += "<label for='pass'>Password: &nbsp</label>";
  content += "<input type='password' id='pass' name='pass' placeholder='password'><br><br>";
  content += "<input type='submit' name='SUBMIT' value='Login'></form>" + msg + "</center></body></html>";
  server.send(200, "text/html", content);
}

void handleRoot() {
  String content = "<!DOCTYPE html><html>";
  content += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  content += "<link rel='icon\' href='data:,\'>";
  content += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto;}</style></head>"; 
  content += "<body><h1><center>CONTROL LED</center></h1><br>";
  content += "<center><form action='/ledon' method='POST'><input type='submit' value='ON'>  &nbsp";
  content += "<input type='submit' formaction='/ledoff' value='OFF'></form></center><br>";
  content += "<center><form action='/update' method='POST'><input type='submit' value='SHOW VALUE'></form></center><br>"; 
  content += "<form action='/sendata' method='POST'><center>";
  content += "<label for='dataf'>Data1: &nbsp</label>"; 
  content += "<input type='text' id='dataf' name='dataf'><br><br>";
  content += "<label for='datas'>Data2: &nbsp</label>";
  content += "<input type='text' id='datas' name='datas'><br><br>";
  content += "<label for='datat'>Data3: &nbsp</label>";
  content += "<input type='text' id='datat' name='datat'><br><br>";
  content += "<input type='submit' value='SEND'></center></form><br>";
  //content += "<a href=\"/login?DISCONNECT=YES\">LOG OUT</a></center></body></html>";
  content += "<center><form action='/login?DISCONNECT=YES' method='POST'><input type='submit' value='Logout'></form></center></body></html>";
  server.send(200, "text/html", content);
}

void handleUpdate(){
  static long layernumber;
  long randnumber = random(20, 100);
  long prerandnumber = layernumber;
  layernumber = randnumber;
  while(!timeClient.update()) 
  {
    timeClient.forceUpdate();
  }
  static String layerTime;
  formattedTime = timeClient.getFormattedTime();
  String preformattedTime = layerTime;
  layerTime = formattedTime;
  String content = "<!DOCTYPE html><html>";
  content += "<head><meta name='viewport' content='width=device-width, initial-scale=1'>";
  content += "<meta http-equiv='refresh' content='20'>";
  content += "<link rel='icon\' href='data:,\'>";
  content += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; }</style></head><body>";
  content += "<center><table><tr><th>VALUE</th><th>TimeStamp</th></tr>";
  content += "<tr><td>";
  content += randnumber;
  content += "</td><td><span class=\"sensor\">";
  content += formattedTime;
  content += "</span></td></tr>";
  content += "<tr><td>";
  content += prerandnumber;
  content += "</td><td><span class=\"sensor\">";
  content += preformattedTime;
  content += "</span></td></tr>";
  content += "</center></body></html>";
  server.send(200, "text/html", content);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/ledon", LEDON);
  server.on("/ledoff", LEDOFF);
  server.on("/sendata", handleSend);
  server.on("/update", handleUpdate);
  server.onNotFound(handleNotFound);
  server.begin();
  timeClient.begin();
  timeClient.setTimeOffset(25200); //7*3600 = 25200
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
