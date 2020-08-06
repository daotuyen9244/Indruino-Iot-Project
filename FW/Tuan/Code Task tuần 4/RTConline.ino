#include                              <time.h>                              // Cho tính toán thời gian
#include                              <WiFi.h>                              // cho wifi
#include                              <WiFiUdp.h>                           // cho upd wifi
#include                              <U8g2lib.h>                           // xem tại https://github.com/olikraus/u8g2/wiki/u8g2reference

#define   FONT_ONE_HEIGHT               8                                   // chiều cao phông chữ 1
#define   FONT_TWO_HEIGHT               20                                  // chiều cao phông chữ 2
#define   NTP_DELAY_COUNT               20                                  // thời gian trễ để cập nhật time 20ms
#define   NTP_PACKET_LENGTH             48                                  // chiều dài gói ntp
#define   TIME_ZONE                     (+7)                                // mã vùng giờ thế giới
#define   UDP_PORT                      4000                                // Port dùng UDP

char      chBuffer[128];                                                    // độ dài chuỗi chung
char      chSSID[] =                      "Indruino_Student";               // tên wifi
char      chPassword[] =                  "Indruino2019";                   // mật khẩu wifi                     
bool      bTimeReceived =                 false;                            // thời gian chưa nhận được
U8G2_SSD1306_128X64_NONAME_F_HW_I2C       u8g2(U8G2_R0, 16, 15, 4);         // OLED graphics
int       nWifiStatus =                   WL_IDLE_STATUS;                   // trạng thái wifi
WiFiUDP   Udp;

void setup()
{
  // OLED graphics.
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
 
  // Wifi.

    // Display title.
    
    u8g2.clearBuffer();
    sprintf(chBuffer, "%s", "Connecting to:");
    u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
    sprintf(chBuffer, "%s", chSSID);
    u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 31 - (FONT_ONE_HEIGHT / 2), chBuffer);
    u8g2.sendBuffer();

    // Connect to wifi.

    Serial.print("NTP clock: connecting to wifi");
    WiFi.begin(chSSID, chPassword);
    while(WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    sprintf(chBuffer, "NTP clock: WiFi connected to %s.", chSSID);
    Serial.println(chBuffer);
    
    // Display connection stats.

      // Clean the display buffer.
      
      u8g2.clearBuffer();
  
      // Display the title.

      sprintf(chBuffer, "%s", "WiFi Stats:");
      u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
  
      // Display the ip address assigned by the wifi router.
      
      char  chIp[81];
      WiFi.localIP().toString().toCharArray(chIp, sizeof(chIp) - 1);
      sprintf(chBuffer, "IP  : %s", chIp);
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 2, chBuffer);
  
      // Display the ssid of the wifi router.
      
      sprintf(chBuffer, "SSID: %s", chSSID);
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 3, chBuffer);
  
      // Display the rssi.
      
      sprintf(chBuffer, "RSSI: %d", WiFi.RSSI());
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 4, chBuffer);

      // Display waiting for ntp message.
      
      u8g2.drawStr(0, FONT_ONE_HEIGHT * 6, "Awaiting NTP time...");

      // Now send the display buffer to the OLED.
      
      u8g2.sendBuffer();

  // Udp.
  
  Udp.begin(UDP_PORT);
}

void  loop()
{
  // Local variables.

  static  int   nNtpDelay = NTP_DELAY_COUNT;
  static  byte  chNtpPacket[NTP_PACKET_LENGTH];

  // Check for time to send ntp request.

  if(bTimeReceived == false)
  {
     // Have yet to receive time from the ntp server, update delay counter.
      
      nNtpDelay += 1;
  
      // Check for time to send ntp request.
      
      if(nNtpDelay >= NTP_DELAY_COUNT)
      {
          // Time to send ntp request, reset delay.
    
          nNtpDelay = 0;
        
          // Send ntp time request.
            
            // Initialize ntp packet.
          
                // Zero out chNtpPacket.
              
                memset(chNtpPacket, 0, NTP_PACKET_LENGTH);
          
                // Set the ll (leap indicator), vvv (version number) and mmm (mode) bits.
                //  
                //  These bits are contained in the first byte of chNtpPacker and are in
                // the following format:  llvvvmmm
                //
                // where:
                //
                //    ll  (leap indicator) = 0
                //    vvv (version number) = 3
                //    mmm (mode)           = 3
                
                chNtpPacket[0]  = 0b00011011;
        
            // Send the ntp packet.
            
            IPAddress ipNtpServer(129, 6, 15, 28);
            Udp.beginPacket(ipNtpServer, 123);
            Udp.write(chNtpPacket, NTP_PACKET_LENGTH);
            Udp.endPacket();

            Serial.println("NTP clock: ntp packet sent to ntp server.");
            Serial.print("NTP clock: awaiting response from ntp server");
      }
      
      Serial.print(".");
      
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
              
              // Output date and time to serial.
              
              struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
              strftime (chBuffer, sizeof(chBuffer), "%a, %d %b %Y %H:%M:%S",  tmPointer);
              Serial.println();
              Serial.print("NTP clock: response received, time written to ESP32 rtc: ");
              Serial.println(chBuffer); 

              // No longer need wifi.

              WiFi.mode(WIFI_OFF);
          }
          else
          {
              // Server did not respond.
              
              Serial.println("NTP clock: packet not received.");
          }
      }
  }
  
  // Update OLED.

  if(bTimeReceived)
  {
      // Ntp time has been received, ajusted and written to the ESP32 rtc, so obtain the time from the ESP32 rtc.
      
      struct  timeval tvTimeValue;
      gettimeofday(& tvTimeValue, NULL);
  
      // Erase the display buffer.
      
      u8g2.clearBuffer();
  
      // Obtain a pointer to local time.
      
      struct tm * tmPointer = localtime(& tvTimeValue.tv_sec);
    
      // Display the date.
  
      strftime(chBuffer, sizeof(chBuffer), "%a, %d %b %Y",  tmPointer);
      u8g2.setFont(u8g2_font_6x10_tr);
      u8g2.drawStr(64 - (u8g2.getStrWidth(chBuffer) / 2), 0, chBuffer);
  
      // Display the time.
      
      strftime(chBuffer, sizeof(chBuffer), "%I:%M:%S",  tmPointer);
      u8g2.setFont(u8g2_font_fur20_tn);
      u8g2.drawStr(10, 63 - FONT_TWO_HEIGHT, chBuffer);
  
      // Send the display buffer to the OLED
      
      u8g2.sendBuffer();
  }
    
  // Give up some time.

  delay(200);
}
