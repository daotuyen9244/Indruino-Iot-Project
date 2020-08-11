// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>  
#include "heltec.h"
#include "RTClib.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void setup () {
  Serial.begin(115200);

#ifndef ESP32
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin(4,15)) {
    Serial.println("Couldn't find RTC");
  }
  
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
     //rtc.adjust(DateTime(2020, 8, 4, 23, 27, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
   rtc.adjust(DateTime(2020, 8, 4, 23, 59, 50));
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_16);
}

void loop () {
    DateTime now = rtc.now();    
    String data1 ="";
    String data2 ="";
    data1 = (String)daysOfTheWeek[now.dayOfTheWeek()] + ", " + (String)now.day() +" : " +(String)now.month()+" : "+(String)now.year();
    data2 = (String)now.hour() +" : " +(String)now.minute()+" : "+(String)now.second();
    Heltec.display->clear();
    Heltec.display->drawString(0,0, data1);
    Heltec.display->drawString(30,30, data2);
    Heltec.display->display();
}
