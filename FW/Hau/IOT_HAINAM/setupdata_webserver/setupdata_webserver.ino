#define SerialDebug

#include "indruino_data.h"

Indruino indruino;

#include "webserver_function.h"

#include "Button_Function.h"
#include "heltec.h"



void showText(int x, int y, String data_, const uint8_t *Font = ArialMT_Plain_10, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment = TEXT_ALIGN_LEFT);
void showText(int x, int y, char *data_, const uint8_t *Font = ArialMT_Plain_10, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment = TEXT_ALIGN_LEFT);

void setup()
{
  // put your setup code here, to run once:

  indruino.init();
  initLCD();
  setupButton();
  Serial.begin(9600);
  if (!read_EEPROM())
  {

    init_webServer();
    // char buffer[20] = {0};
    // sprintf(buffer,"%s", );
    showText(0, 30, ssid_ap);
    showText(0, 40, pass_ap);
    showText(0, 50, WiFi.softAPIP().toString().c_str());
    while (true) //server handle
    {
      webServer.handleClient();
    }
  }
  else
  {
    Heltec.display->clear();
    Heltec.display->setColor(WHITE);
    showText(0, 0, ssid);
    showText(0, 10, pass);
  }
}

void loop()
{
  buttonAlive();
  check_btn_press();
  if (KeyCode == keySetup)
  {
    Heltec.display->clear();
    Heltec.display->setColor(WHITE);
    showText(0, 0, "Go to setup esp");
    delay(200);
    indruino.myRom()->writeChar(Rom_check_data, 0x00);
    ESP.restart();
  }
  // put your main code here, to run repeatedly:
}
void initLCD()
{
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
  Heltec.display->display();
}
void showText(int x, int y, String data_, const uint8_t *Font, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment)
{
  Heltec.display->setTextAlignment(textAlignment);
  Heltec.display->setFont(Font);
  Heltec.display->drawString(x, y, data_);
  Heltec.display->display();
}
void showText(int x, int y, char *data_, const uint8_t *Font, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment)
{
  Heltec.display->setTextAlignment(textAlignment);
  Heltec.display->setFont(Font);
  Heltec.display->drawString(x, y, String(data_));
  Heltec.display->display();
}
