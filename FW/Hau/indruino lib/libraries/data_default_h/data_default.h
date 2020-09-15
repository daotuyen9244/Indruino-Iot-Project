#ifndef _DATA_DEFAULT_H
#define _DATA_DEFAULT_H
//DATA DEFAULT CONFIG PROTOCOL

typedef struct _data_default
{
//model
const char* model = PSTR("F1");
//firmware
const char* fw = PSTR("00");
//id
const char* id = PSTR("0000");
//baud
const unsigned char baud_mode = 0; 
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

//mode protocol
    
    

   











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

    //data comunication
        //Uchar 64
        //char 64
        //uint16 32
        //int16 32
        //float 10
        //double 10
    //data comunication

 } Data_Default;

 typedef struct _wifi_default
 {
     //WiFi
        //ModeWifi
        const unsigned char _mWiFi = 0; //mode WiFi
        //
        //0 mode Station
        //1 mode Access Point AP
        //
        //ModeWifi

        //ModeIP
        const unsigned char _mIP = 0; //mode IP
        //
        //mode = 0 static
        //mode = 1 dynamic
        //
        //ModeIP


        //IP
        const unsigned char _IP[4] = {192,168,100,10};
        //GW
        const unsigned char _GW[4] = {0,0,0,0};
        //sub
        const unsigned char _SB[4] = {0,0,0,0};
        //user
        const unsigned char _user[20] = {0};
        //mac
        const unsigned char _mac[6] = {0};
        //pass
        const unsigned char _pass[20] = {0}; 
    //WiFi
 } WiFi_Default;
   
typedef struct _mqtt_default
{
    //mqtt
        //ip broker
        //user
        //pass
        //qos
        //port
        //goi tin alive
        //goitinsend2broker
    //mqtt
} MQTT_Default;

typedef struct _udp_default
{
   //udp
        //ip
        //port
    //udp
}UDP_Default;

typedef struct _tcp_default
{
    //tcp
        //ip
        //port
    //tcp
}TCP_Default;

typedef struct _ftp_default
{
    //FTP
        //ip server
        //user
        //pass
        //port
    //FTP
} FTP_Default;

typedef struct _modbus_rtu_default
{
    //modbus RTU
        //ID
        //Baud
    //modbusRTU
}MODBUS_RTU_Default;

typedef struct _modbus_tcp_default
{
    //modbus tcp
        //ip
        //port
    //modbus tcp
}MODBUS_TCP_Default;

typedef struct _data_logging
{
    //data logging
        //mode
        //type
    //data logging
}Data_Logging_Default;

typedef struct _server_storage
{
    //server storage
        //mode
        //IP
        //user
        //pass 
    //server storage
} SERVER_STORAGE_Default;

typedef struct _time_default
{
    //time
        //mode
        //year
        //month
        //date
        //date of week
        //hour
        //minute
        //second
    //time
}TIME_Default;





#endif //_DATA_DEFAULT_H