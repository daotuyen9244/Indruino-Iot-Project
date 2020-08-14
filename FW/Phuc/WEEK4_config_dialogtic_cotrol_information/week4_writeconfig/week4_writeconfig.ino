#include <FS.h>          // this needs to be first, or it all crashes and burns...
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h> // https://github.com/bblanchon/ArduinoJson
#ifdef ESP32
  #include <SPIFFS.h>
#endif
char mqtt_mode[20]="";
char mqtt_server[40]="";
char mqtt_port[6]  = "8080";
char api_token[32];
char mqtt_user[40];
char mqtt_pass[40];
char mqtt_Qos[32];
char mqtt_mgs[40];

char wifimode[16]="STATIC";
char static_ip[16]="192.168.1.110";
char static_gw[16]="192.168.1.1";
char static_sn[16]="255.255.255.0";

bool shouldSaveConfig = false;

void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setupSpiffs(){
  Serial.println("mounting FS...");
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(mqtt_mode, json["mqtt_mode"]);
          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(api_token, json["api_token"]);
          strcpy(mqtt_user, json["mqtt_user"]);
          strcpy(mqtt_pass, json["mqtt_pass"]);
          strcpy(mqtt_Qos, json["mqtt_Qos"]);
          strcpy(mqtt_mgs, json["mqtt_mgs"]);

          if(json["ip"]) {
            Serial.println("setting custom ip from config");
            strcpy(wifimode, json["wifimode"]);
            strcpy(static_ip, json["ip"]);
            strcpy(static_gw, json["gateway"]);
            strcpy(static_sn, json["subnet"]);
            Serial.println(static_ip);
          } else {
            Serial.println("no custom ip in config");
          }

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  setupSpiffs();
  WiFiManager wm;
  wm.setSaveConfigCallback(saveConfigCallback);
  
  WiFiManagerParameter custom_wifi_mode("wifimode", "set DHCP or STATIC", wifimode, 10);
  WiFiManagerParameter custom_mqtt_mode("mode", "mqtt mode (get/post)", mqtt_mode, 10);
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  WiFiManagerParameter custom_api_token("api", "api token", api_token, 32);
  WiFiManagerParameter custom_mqtt_user("mquser", "mqtt user", mqtt_user, 40);
  WiFiManagerParameter custom_mqtt_pass("mqpass", "mqtt password", mqtt_pass, 40);
  WiFiManagerParameter custom_mqtt_qos("mqqos", "mqtt Qos", mqtt_Qos, 32);
  WiFiManagerParameter custom_mqtt_mgs("mqmgs", "mqtt message", mqtt_mgs, 32);

  wm.addParameter(&custom_wifi_mode);
  wm.addParameter(&custom_mqtt_mode);
  wm.addParameter(&custom_mqtt_server);
  wm.addParameter(&custom_mqtt_port);
  wm.addParameter(&custom_api_token);
  wm.addParameter(&custom_mqtt_user);
  wm.addParameter(&custom_mqtt_pass);
  wm.addParameter(&custom_mqtt_qos);
  wm.addParameter(&custom_mqtt_mgs);

  IPAddress _ip,_gw,_sn;
  _ip.fromString(static_ip);
  _gw.fromString(static_gw);
  _sn.fromString(static_sn);
  strcpy(wifimode, custom_wifi_mode.getValue());
  if(strcmp(wifimode,"STATIC")==0)
   wm.setSTAStaticIPConfig(_ip, _gw, _sn);
  //wm.resetSettings();
  
  if (!wm.autoConnect("AutoConnectAP", "password")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    // if we still have not connected restart and try all over again
    ESP.restart();
    delay(5000);
  }

  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_mode, custom_mqtt_mode.getValue());
  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(api_token, custom_api_token.getValue());
  strcpy(mqtt_user, custom_mqtt_user.getValue());
  strcpy(mqtt_pass, custom_mqtt_pass.getValue());
  strcpy(mqtt_Qos, custom_mqtt_qos.getValue());
  strcpy(mqtt_mgs, custom_mqtt_mgs.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_mode"] = mqtt_mode;
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"]   = mqtt_port;
    json["api_token"]   = api_token;
    json["mqtt_user"]   = mqtt_user;
    json["mqtt_pass"]   = mqtt_pass;
    json["mqtt_Qos"]   = mqtt_Qos;
    json["mqtt_mgs"]   = mqtt_mgs;
    json["wifimode"] = wifimode;
    json["ip"]          = WiFi.localIP().toString();
    json["gateway"]     = WiFi.gatewayIP().toString();
    json["subnet"]      = WiFi.subnetMask().toString();

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
    shouldSaveConfig = false;
  }

  Serial.println("local ip");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.subnetMask());
}

void loop() {
  // put your main code here, to run repeatedly:


}
