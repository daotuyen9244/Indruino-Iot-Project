#ifndef _BARCODE_SCANNER_H
#define _BARCODE_SCANNER_H
#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

#define length_char 15
char barcode_data[length_char] ="";
char *pch = barcode_data;

extern bool do_import_data_barcode(char *data);
extern bool do_import_data_barcode(char *data);
extern void refresh_btnCode_lcd(char *data);
class KbdRptParser : public KeyboardReportParser
{
  protected:
    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii4Barcode(mod, key);
  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
  #ifdef SerialDebug
  Serial.print((char)key);
  #endif
  *(pch++) =(char)key;
  if(key == 0x0D)
  {
    *pch = '\0';
    //
    refresh_btnCode_lcd(barcode_data);
    do_import_data_barcode(barcode_data);
    
    for(uint8_t i = 0; i < length_char; i++)
    {
      barcode_data[i] = ' ';
    }
    pch = barcode_data;
  #ifdef SerialDebug
    Serial.println("done");
  #endif
  } 
};

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
KbdRptParser Prs;
#endif