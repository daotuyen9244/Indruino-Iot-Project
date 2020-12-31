// #include <usbhid.h>
// #include <usbhub.h>
// #include <hiduniversal.h>
// #include <hidboot.h>

// class MyParser : public HIDReportParser {
//   public:
//     MyParser();
//     void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
//   protected:
//     uint8_t KeyToAscii(bool upper, uint8_t mod, uint8_t key);
//     virtual void OnKeyScanned(bool upper, uint8_t mod, uint8_t key);
//     virtual void OnScanFinished();
// };
// MyParser::MyParser(){}
// void MyParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
//   // If error or empty, return
//  // if (buf[2] == 1 || buf[2] == 0) return;

//   for (uint8_t i = 15; i >= 2; i--) {
//     // If empty, skip
//     if (buf[i] == 0) continue;

//     // If enter signal emitted, scan finished
//     if (buf[i] == UHS_HID_BOOT_KEY_ENTER) {
//       OnScanFinished();
//     }

//     // If not, continue normally
//     else {
//       // If bit position not in 2, it's uppercase words
//       OnKeyScanned(i > 2, *buf, buf[i]);
//     }

//     return;
//   }
// }

// uint8_t MyParser::KeyToAscii(bool upper, uint8_t mod, uint8_t key) {
//   // Letters
//   if (VALUE_WITHIN(key, 0x04, 0x1d)) {
//     if (upper) return (key - 4 + 'A');
//     else return (key - 4 + 'a');
//   }

//   // Numbers
//   else if (VALUE_WITHIN(key, 0x1e, 0x27)) {
//     return ((key == UHS_HID_BOOT_KEY_ZERO) ? '0' : key - 0x1e + '1');
//   }

//   return 0;
// }

// void MyParser::OnKeyScanned(bool upper, uint8_t mod, uint8_t key) {
//   uint8_t ascii = KeyToAscii(upper, mod, key);
//   // hasil = hasil + (char)ascii;
//   Serial.print((char)ascii);
// }

// void MyParser::OnScanFinished() {

// }

// USB          Usb;
// //USBHub       Hub(&Usb);
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    Hid(&Usb);
// MyParser     Parser;

// void setup()
// {
//   Serial.begin(9600);
//   if (Usb.Init() == -1) {
//     Serial.println("OSC did not start.");
//   }
//   delay(200);
//   Hid.SetReportParser(0, &Parser);
// }

// void loop()
// {
//   Usb.Task();
// }

// #include <hidboot.h>
// #include <usbhub.h>

// // Satisfy the IDE, which needs to see the include statment in the ino too.
// #ifdef dobogusinclude
// #include <spi4teensy3.h>
// #endif
// #include <SPI.h>
// #include <hidboot.h>
// #include <usbhub.h>


// class KbdRptParser : public KeyboardReportParser
// {
//   protected:
//     void OnKeyDown	(uint8_t mod, uint8_t key);
//     void OnKeyPressed(uint8_t key);
// };

// void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
// {
//   uint8_t c = OemToAscii4Barcode(mod, key);
//   if (c)
//     OnKeyPressed(c);
// }

// void KbdRptParser::OnKeyPressed(uint8_t key)
// {
//   Serial.println(key, HEX);
//   if(key == 0x28) Serial.println("done");
// }

// USB     Usb;
// //USBHub     Hub(&Usb);
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
// KbdRptParser Prs;

char* do_import_data(char *data);
#include "barcode_scanner.h"
#include <WiFi.h>
#include <HTTPClient.h>


const char* page_insert_db= "/Insert_db.php"; //tao user moi
// const char* page_pay_db = "/Pay_db.php"; //tra phi
// const char* page_read_db = "/Read_db.php"; //doc du lieu tu server
// const char* page_update_db = "/Update_db.php"; //nap tien server

const char* url_service = "http://192.168.100.44/iot_hainam";

const char *ssid = "Trung Tam Nghien Cuu";
const char *password = "Indruino2020";

void connect_wifi();

void setup()
{

  Serial.begin(115200);
  connect_wifi();

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay(200);

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop()
{
  Usb.Task();
}
char* do_import_data(char *data)
{
  String _reData = "";
  String postData = "";
  if ((WiFi.status() == WL_CONNECTED))
  {
    WiFiClient client;
    HTTPClient http;
    String page = String(url_service) + String(page_insert_db);
    http.begin(client, page);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    postData = "data=" + String(data);
    // Serial.println("POst");

    int httpCode = http.POST(postData);
    //Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode > 0)
    {

      if (httpCode == HTTP_CODE_OK)
      {
        int len = http.getSize();
        uint8_t buff[128] = {0};

        WiFiClient *stream = &client;
        while (http.connected() && (len > 0 || len == -1))
        {

          int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));

          //USE_SERIAL.write(buff, c);
          String tmp = (String)(char *)buff;
          //
          //
          _reData += tmp.substring(0, c);
          if (len > 0)
          {
            len -= c;
          }
        }
        //_reData += '}';
        Serial.println();
        Serial.print("respond: ");
        Serial.println(_reData);
        _reData = _reData.substring(2, _reData.length() - 2);
        return (char *)_reData.c_str();
      }
      else
      {
      }
      http.end();
    }
  }
  else
    Serial.println("{error}");
}

void connect_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}