#include <WiFi.h>

const char* ssid = "Toi Yeu Viet Nam";
const char* password = "khongnhopass";

WiFiServer server(8088);

void setup()
{
    Serial.begin(115200);
    Serial.print("Connecting to ");
    
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}
void loop(){
    /* listen for client */
    WiFiClient client = server.available(); 
    uint8_t data[30]; 
    if (client) {                   
      Serial.println("new client");         
      /* check client is connected */           
      while (client.connected()) {          
          if (client.available()) {
              int len = client.read(data, 30);
              if(len < 30){
                  data[len] = '\0';  
              }else {
                  data[30] = '\0';
              }    
              Serial.print("client sent: ");            
              Serial.println((char *)data); 
          }
      } 
    }
}
