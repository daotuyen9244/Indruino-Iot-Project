#include<time.h>                             
#include<WiFi.h>                             
#include<WiFiUdp.h>  
#include<Wire.h>
#include "heltec.h"                         
                           
#define   NTP_DELAY_COUNT               20                                  
#define   NTP_PACKET_LENGTH             48                                  
#define   TIME_ZONE                     (+7)                                
#define   UDP_PORT                      4000                                

char      chBuffer[128];                                                    
char      chSSID[] =                      "Trung Tam Nghien Cuu";            
char      chPassword[] =                  "Indruino2020" ;                               
bool      bTimeReceived =                 false;                            
int       nWifiStatus =                   WL_IDLE_STATUS;                  
WiFiUDP   Udp;

void setup()
{ 
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
    Heltec.display->init();
    Heltec.display->flipScreenVertically();
    Heltec.display->setFont(ArialMT_Plain_10);
    
    sprintf(chBuffer, "%s", "Connecting to:");
    Heltec.display->drawString(64-(Heltec.display->getStringWidth(chBuffer)/2), 0, chBuffer);
    sprintf(chBuffer, "%s", chSSID);
    Heltec.display->drawString(64-(Heltec.display->getStringWidth(chBuffer)/2), 30, String(chBuffer));
    Heltec.display->display();
  
    WiFi.begin(chSSID, chPassword);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    
    Heltec.display->clear();
    sprintf(chBuffer, "%s", "WiFi Stats:");
    Heltec.display->drawString(64-(Heltec.display->getStringWidth(chBuffer)/2), 0, chBuffer);
    
    char  chIp[81];
    WiFi.localIP().toString().toCharArray(chIp, sizeof(chIp) - 1);
    
    sprintf(chBuffer, "IP  : %s", chIp);
    Heltec.display->drawString(0, 20, chBuffer);
    
    sprintf(chBuffer, "SSID: %s", chSSID);
    Heltec.display->drawString(0, 30, chBuffer);
    
    sprintf(chBuffer, "RSSI: %d", WiFi.RSSI());
    Heltec.display->drawString(0, 40, chBuffer);

    Heltec.display->display();
    delay(1000);
    Udp.begin(UDP_PORT);
} 

void  loop()
{
  static  int   nNtpDelay = NTP_DELAY_COUNT;
  static  byte  chNtpPacket[NTP_PACKET_LENGTH];

  if(bTimeReceived == false)
  {
     // Have yet to receive time from the ntp server, update delay counter.
      
      nNtpDelay += 1;
  
      // Check for time to send ntp request.
      
      if(nNtpDelay >= NTP_DELAY_COUNT)
      {
          // Time to send ntp request, reset delay.
    
          nNtpDelay = 0;
              
                memset(chNtpPacket, 0, NTP_PACKET_LENGTH);
                
                chNtpPacket[0]  = 0b00011011;
        
            // Send the ntp packet.
            
            IPAddress ipNtpServer(129, 6, 15, 28);
            Udp.beginPacket(ipNtpServer, 123);
            Udp.write(chNtpPacket, NTP_PACKET_LENGTH);
            Udp.endPacket();
      }
      
      // Check for time to check for server response.
    
      if(nNtpDelay == (NTP_DELAY_COUNT - 1))
      {
          // Time to check for a server response.
          
          if(Udp.parsePacket())
          {
              // Server responded, read the packet.
              
              Udp.read(chNtpPacket, NTP_PACKET_LENGTH);
      
              // Obtain the time from the packet, convert to Unix time, and adjust for the time zone.
      
              struct  timeval tvTimeValue = {0, 0};
              
              tvTimeValue.tv_sec = ((unsigned long)chNtpPacket[40] << 24) +       // bits 24 through 31 of ntp time
                                   ((unsigned long)chNtpPacket[41] << 16) +       // bits 16 through 23 of ntp time
                                   ((unsigned long)chNtpPacket[42] <<  8) +       // bits  8 through 15 of ntp time
                                   ((unsigned long)chNtpPacket[43]) -             // bits  0 through  7 of ntp time
                                   (((70UL * 365UL) + 17UL) * 86400UL) +          // ntp to unix conversion
                                   (TIME_ZONE * 3600UL) +                         // time zone adjustment
                                   (5);                                           // transport delay fudge factor
              
              // Set the ESP32 rtc.
              
              settimeofday(& tvTimeValue, NULL);
              
              // Time has been received.
      
              bTimeReceived = true;
              
              struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
              strftime (chBuffer, sizeof(chBuffer), "%a, %d %b %Y %H:%M:%S",  tmPointer);
              WiFi.mode(WIFI_OFF);
          }
          else
          {
          }
      }
  }

  if(bTimeReceived)
  {    
      struct  timeval tvTimeValue;
      gettimeofday(& tvTimeValue, NULL);

      struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
      
      strftime(chBuffer, sizeof(chBuffer), "%I:%M:%S",  tmPointer);
      Heltec.display->clear();
      Heltec.display->drawString(64-(Heltec.display->getStringWidth(chBuffer)/2), 30, String(chBuffer));
      Heltec.display->display();
  }
}
