#include "Arduino.h"
#include "heltec.h"

void showText(int x, int y , String data_, const uint8_t*Font, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment);

void setup() {
  // put your setup code here, to run once:
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
}
int i = 0;
void loop() {
  showText(0, 0, "ahihi",ArialMT_Plain_10, TEXT_ALIGN_LEFT);
  delay(100);
  showText(0, 50, "test",ArialMT_Plain_10, TEXT_ALIGN_LEFT);
  delay(100);
  // put your main code here, to run repeatedly:

}
void showText(int x, int y, String data_, const uint8_t *Font, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment)
{
  Heltec.display->setTextAlignment(textAlignment);
  Heltec.display->setFont(Font);
  Heltec.display->drawString(y, x, data_);
  Heltec.display->display();
}
