#ifndef WEBSERVER_FUNCTION_H
#define WEBSERVER_FUNCTION_H
#include <WebServer.h>
#include "index.h"

WebServer webServer(80);

char *ssid_ap = "ESP32_AP";
char *pass_ap = "12345678";

String ssid;
String pass;
char ID_board[3];

void mainpage();
void get_IP();
bool read_EEPROM();
void write_EEPROM();
void restart_ESP();
void clear_EEPROM();
void clear_data(); //clear data config (wifi information, id name)

void mainpage()
{
    String s = FPSTR(MainPage);
    webServer.send(200, "text/html", s);
}
void get_IP()
{
    String s = WiFi.localIP().toString();
    webServer.send(200, "text/html", s);
}
boolean read_EEPROM()
{
#ifdef SerialDebug
    Serial.println("Reading EEPROM...");
#endif
    if (indruino.myRom()->readChar(Rom_check_data) == 0x01)
    {
        ssid = "";
        for (int i = Rom_WiFI_User; i < Rom_WiFi_Mac; i++)
        {
            ssid += char(indruino.myRom()->readChar(i));
        }
#ifdef SerialDebug
        Serial.print("SSID: ");
        Serial.println(ssid);
#endif
        pass = "";
        for (int i = Rom_WiFi_Pass; i < Rom_mPrtcol; i++)
        {
            pass += char(indruino.myRom()->readChar(i));
        }
#ifdef SerialDebug
        Serial.print("PASSWORD: ");
        Serial.println(pass);
#endif
        byte id_board = indruino.myRom()->readByte(Rom_IdBr);

        String tmp = String(id_board);
        memcpy(ID_board, tmp.c_str(), tmp.length());
#ifdef SerialDebug
        Serial.print("ID_board: ");
        Serial.println(ID_board);
#endif
        return true;
    }
    else
    {
#ifdef SerialDebug
        Serial.println("Data wifi not found!");
#endif
        //

        //
        return false;
    }
}
void write_EEPROM()
{
#ifdef SerialDebug
    Serial.println("Clear EEPROM!");
#endif
    clear_data();

    //check data
    //check data

    ssid = webServer.arg("ssid");
    for (int i = 0; i < ssid.length(); i++)
    {
        indruino.myRom()->writeChar(Rom_WiFI_User + i, ssid[i]);
    }

    pass = webServer.arg("pass");
    for (int i = 0; i < pass.length(); i++)
    {
        indruino.myRom()->writeChar(Rom_WiFi_Pass + i, pass[i]);
    }
    //int id1, id2, id3, id4;
    //sscanf((webServer.arg("ID_board")).c_str(), "%d.%d.%d.%d", &id1, &id2,&id3, &id4);
    int id_board = webServer.arg("id_board").toInt();
    indruino.myRom()->writeByte(Rom_IdBr, (byte)id_board);

    //indruino.myRom()->writeShort(Rom_mqtt_port, (webServer.arg("port")).toInt());
#ifdef SerialDebug
    Serial.println("Writed to EEPROM!");
#endif
    String s = "Đã lưu thông tin";
    webServer.send(200, "text/html", s);

    indruino.myRom()->writeChar(Rom_check_data, 0x01);
    ESP.restart();
}
void restart_ESP()
{
    ESP.restart();
    String s = "Đã khởi động lại ESP32";
    webServer.send(200, "text/html", s);
}
void clear_EEPROM()
{
#ifdef SerialDebug
    Serial.println("Clear EEPROM!");
#endif
    clear_data();
    String s = "Đã xóa data";
    webServer.send(200, "text/html", s);
}
void clear_data()
{
    for (int i = Rom_WiFI_User; i < Rom_WiFi_Mac; i++)
    {
        indruino.myRom()->writeByte(i, 0);
    }
    for (int i = Rom_WiFi_Pass; i < Rom_mPrtcol; i++)
    {
        indruino.myRom()->writeByte(i, 0);
    }
    for (int i = Rom_IdBr; i < Rom_mNum; i++)
    {
        indruino.myRom()->writeByte(i, 0);
    }
    // for (int i=Rom_mqtt_port; i<Rom_mqtt_topic_lwt; i++)
    // {
    //   indruino.myRom()->writeByte(i, 0);
    // }
}
bool checkDataRom()
{
    if (indruino.myRom()->readChar(Rom_check_data) == 0x01)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool init_webServer()
{
    WiFi.disconnect();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid_ap, pass_ap);
#ifdef SerialDebug
    Serial.println("Soft Access Point mode!");
    Serial.print("Please connect to ");
    Serial.println(ssid_ap);
    Serial.print("Web Server IP Address: ");
#endif
    
#ifdef SerialDebug    
    IPAddress IP = WiFi.softAPIP();
    Serial.println(IP);
#endif
    webServer.on("/", mainpage);
    //webServer.on("/getIP", get_IP);
    webServer.on("/writeEEPROM", write_EEPROM);
    webServer.on("/restartESP", restart_ESP);
    webServer.on("/clearEEPROM", clear_EEPROM);
    webServer.begin();

}


#endif