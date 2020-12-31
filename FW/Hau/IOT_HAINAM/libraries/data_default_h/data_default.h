#ifndef _DATA_DEFAULT_H
#define _DATA_DEFAULT_H
//DATA DEFAULT CONFIG PROTOCOL

#include "config_mem.h"

typedef struct _data_default
{
//model
const char ID_BOARD = PSTR("1");
//firmware
const char model_number = PSTR(0x00);
//id
const char fw_ver = PSTR(0x00);
//baud
//const char baud_s1 = PSTR(0x04); 
/*
            0:300
            1: 1200
            2:2400
            3:4800
            4:9600
            5:19200
            6:38400
            7:57600
            8: 74880
            9: 115200
            10: 230400
            11: 250000
            12: 500000
            13: 1000000
            14: 2000000
*/
//baud   
//const char id_s1 = PSTR(0x00);
const char return_delay = PSTR(0x01);

#ifdef ESP32||ESP8266

//wifi
const WiFi_Data wifi_default;
//mode protocol
const char mode_protocol = PSTR(0x01); //use mqtt

const MQTT_Data mqtt_default;
const UDP_Data udp_default;
const TCP_Data tcp_default;
const MODBUS_RTU_Data modrtu_s1_default;
const MODBUS_TCP_Data modtcp_default;
const FTP_Data ftp_default;
const Data_Logging_Data data_logging_default;
const SERVER_STORAGE_Data sv_storage_default;
const TIME_Data time_default;


#else
const MODBUS_RTU_Data modrtu_s1_default;
const MODBUS_RTU_Data modrtu_s2_default;
#endif
    //digital Input
        //4port
    //digital Input

    //digital output
        //4port
    //digital output

    //analog In
        //8chanel
    //analog In
    //analog out
        //8 chanel
    //analog out


 } Data_Default;

 typedef struct _wifi_data
 {
     //WiFi
        //ModeWifi
        unsigned char _mWiFi = PSTR(0); //mode WiFi
        //
        //0 mode Station
        //1 mode Access Point AP
        //
        //ModeWifi
        
        //ModeIP
        unsigned char _mIP = PSTR(0); //mode IP
        //
        //mode = 0 static
        //mode = 1 dynamic
        //

        //ModeIP
        //IP
        unsigned char _IP[4] PROGMEM = {192,168,100,10};
        //GW
         unsigned char _GW[4] PROGMEM= {0,0,0,0};
        //sub
         unsigned char _SB[4] PROGMEM= {0,0,0,0};
        //user
         unsigned char _user[20] PROGMEM= {0};
        //mac
         unsigned char _mac[6] PROGMEM= {0};
        //pass
         unsigned char _pass[20] PROGMEM = {0}; 
    //WiFi
 } WiFi_Data;
   
typedef struct _mqtt_data
{
    //mqtt
        //ip broker
         unsigned char _IP[4] PROGMEM= {45,77,45,244};
        //user
         unsigned char _user[20] PROGMEM= {0};
        //pass
         unsigned char _pass[20] PROGMEM= {0};
        //qos
         unsigned char _qos PROGMEM= {0};
        //port
         unsigned short _port PROGMEM= 1883;
        //goi tin alive - lwt
         unsigned char _topic[20] PROGMEM= {0}; //name of esp
         unsigned char _payload PROGMEM= 0;
         unsigned char _returned PROGMEM= 1;
        //goitinsend2broker

    //mqtt
} MQTT_Data;

typedef struct _udp_data
{
   //udp
        //ip
         unsigned char _IP[4] PROGMEM= {0};
        //port
         unsigned short _port[4] PROGMEM= {0};
    //udp
}UDP_Data;

typedef struct _tcp_data
{
    //tcp
        //ip
         unsigned char _IP[4] PROGMEM= {0};
        //port
         unsigned short _port[4] PROGMEM= {0};
    //tcp
}TCP_Data;

typedef struct _ftp_data
{
    //FTP
        //ip server
         unsigned char _IP[4] PROGMEM= {0};
        //user
         unsigned char _user[20] PROGMEM= {0};
        //pass
         unsigned char _pass[20] PROGMEM= {0};
        //port
         unsigned short _port PROGMEM= 0;
    //FTP
} FTP_Data;

typedef struct _modbus_rtu_data
{
    //modbus RTU
        //ID
#ifdef ESP32 || ESP8266
         unsigned char _ID = 0;
#else
         unsigned char _ID = 1;
#endif
        //Baud
         unsigned char _baud PROGMEM= 0x04; //baud 9600
    //modbusRTU
}MODBUS_RTU_Data;

typedef struct _modbus_tcp_data
{
    //modbus tcp
        //ip
         unsigned char _IP[4] PROGMEM= {0};
        //port
         unsigned short _port PROGMEM= 0;
    //modbus tcp
}MODBUS_TCP_Data;

typedef struct _data_logging_data
{
    //data logging
        //mode
         unsigned char _mode PROGMEM= 0;
        //
        //
        //
        //type
         unsigned char _type PROGMEM= 0;
    //data logging
}Data_Logging_Data;

typedef struct _server_storage_data
{
    //server storage
        //mode
         unsigned char _mode PROGMEM= 0;
        //
        //
        //
        //IP
         unsigned char _IP[4] PROGMEM= {0};
        //user
         unsigned char _user[20] PROGMEM= {0};
        //pass 
         unsigned char _pass[20] PROGMEM= {0};
    //server storage
} SERVER_STORAGE_Data;

typedef struct _time_data
{
    //time
        //mode
         unsigned char _mode PROGMEM= 0;
        //0: 
        //1: setup

        //year
         unsigned char _year PROGMEM= 0;
        //month
         unsigned char _month PROGMEM= 0;
        //date
         unsigned char _date PROGMEM= 0;
        //date of week
         unsigned char _dow PROGMEM= 1;
        //hour
         unsigned char _hour PROGMEM= 0;
        //minute
         unsigned char _min PROGMEM= 0;
        //second
         unsigned char _sec PROGMEM= 0;
    //time
}TIME_Data;

#endif //_DATA_DEFAULT_H  