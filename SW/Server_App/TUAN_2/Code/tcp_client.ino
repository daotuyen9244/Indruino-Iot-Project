#include <WiFi.h>
/* change ssid and password according to yours WiFi*/
const char* ssid = "Toi Yeu Viet Nam";
const char* password = "khongnhopass";
/*
 * This is the IP address of your PC
 * [Wins: use ipconfig command, Linux: use ifconfig command]
*/
const char* host = "192.168.43.77";
const int port = 8088;
void setup()
{
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* connect to your WiFi */
    WiFi.begin(ssid, password);
    /* wait until ESP32 connect to WiFi*/
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
}
void loop()
{
    delay(100);
    Serial.print("connecting to ");
    Serial.println(host);
    /* Use WiFiClient class to create TCP connections */
    WiFiClient client;
    
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        return;
    }
    /* This will send the data to the server */
    client.println("hello world");
    client.stop();
}
