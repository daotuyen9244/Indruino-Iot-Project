//#define SerialDebug
void refresh_btnCode_lcd(char *data); //need to fix it
#include "Arduino.h"
#include "heltec.h"
#include "images.h"

#include "indruino_data.h"
Indruino indruino;

#include "webserver_function.h"
#include "Button_Function.h"
#include "barcode_scanner.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

bool do_import_data_barcode(char *data);
typedef struct
{
  unsigned long last_value = 0;
  unsigned long curr_value = 0;
  unsigned long time_delay = 0;
  bool run = false;
} timerTick_;

#define time_clear_btnCode 1000
timerTick_ timer_clear_btnCode;

//const char *ID_board = "1";

void enableTimer_databtn(timerTick_ &timer = timer_clear_btnCode);
void clear_btnCode_lcd();

// void showNameButton_lcd(char *data);
void btnEvent_Service();
void check_clear_btnCode_lcd(timerTick_ &timer = timer_clear_btnCode);
//button

//for db
const char *url_service = "http://5fc1b1e2cb4d020016fe6bc0.mockapi.io/esp_client";

// const char *ssid = "TruongHau2.4";
// const char *password = "26309224";
void connect_wifi();
// void Http_Patch()
timerTick_ timer_get_product_code;
char *get_data_db(const char *data = ID_board); //get productcode
bool patch_data_button_db(char *data);

//

void decodeJson(String &data); // decode productcode
void decodeJson(char *_data);
//
//for db

//for lcd

timerTick_ timer_clear_status;
void enableTimerTick(timerTick_ &timer = timer_clear_status); //lcd
#define time_set_clear 500                                    //for clear status
void initLCD();
void wifi_icon();
void send_ok_lcd();
void send_error_lcd();
void clear_send_status_lcd();
void refresh_product_code_lcd(char *data); //in chuoi productCode
char last_ProductOrtherCode[45] = {0};
#define time_check_new_product 10000
void check_new_product_code(timerTick_ &timer = timer_get_product_code);
void check_clear_status_lcd(timerTick_ &time = timer_clear_status); //kiem tra sau do clear data
void showText(int x, int y, String data_, const uint8_t *Font = ArialMT_Plain_10, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment = TEXT_ALIGN_LEFT);
void showText(int x, int y, char *data_, const uint8_t *Font = ArialMT_Plain_10, OLEDDISPLAY_TEXT_ALIGNMENT textAlignment = TEXT_ALIGN_LEFT);
//for lcd

void setup()
{

  indruino.init();
  initLCD();

  setupButton(); //thiet lap thoi gian debounce
#ifdef SerialDebug
  
#endif
  Serial.begin(9600);
  if (!read_EEPROM())
  {
    init_webServer();
    showText(0, 30, ssid_ap);
    showText(0, 40, pass_ap);
    showText(0, 50, WiFi.softAPIP().toString().c_str());
    while (true)
    {
      webServer.handleClient();
    }
  }
  else
  {
    showText(0, 0, String("ID: ") + String(ID_board));
    connect_wifi();
    send_ok_lcd();
    char *pch = get_data_db(ID_board);
    decodeJson(pch);

    if (Usb.Init() == -1)
    {
#ifdef SerialDebug
      Serial.println("OSC did not start.");
#endif
    }
    delay(200);
    HidKeyboard.SetReportParser(0, &Prs);
    //add vao ham init
    timer_get_product_code.time_delay = time_check_new_product;
    timer_clear_btnCode.time_delay = time_clear_btnCode;
    timer_clear_status.time_delay = time_set_clear;
    //add vao ham init

    // patch_data_button_db("test_nut_nhan"); // gioi han do chuoi tren db max 5 kytu
    /* code */
  }

  //   showText(0, 0, String("ID: ") + String(ID_board));
  //   connect_wifi();
  //   send_ok_lcd();
  //   char *pch = get_data_db(ID_board);
  //   decodeJson(pch);

  //   if (Usb.Init() == -1)
  //   {
  // #ifdef SerialDebug
  //     Serial.println("OSC did not start.");
  // #endif
  //   }
  //   delay(200);
  //   HidKeyboard.SetReportParser(0, &Prs);
  //   //add vao ham init
  //   timer_get_product_code.time_delay = time_check_new_product;
  //   timer_clear_btnCode.time_delay = time_clear_btnCode;
  //   timer_clear_status.time_delay = time_set_clear;
  //   //add vao ham init

  //   // patch_data_button_db("test_nut_nhan"); // gioi han do chuoi tren db max 5 kytu
}
int i = 0;
void loop()
{
  Usb.Task();
  buttonAlive(); //alive for button
  //check wifi
  //check wifi
  check_clear_status_lcd();

  check_new_product_code();
  check_btn_press();
  btnEvent_Service();
  check_clear_btnCode_lcd();

  // showText(0, 0, "ahihi",ArialMT_Plain_10, TEXT_ALIGN_LEFT);
  // delay(100);
  // showText(0, 50, "test",ArialMT_Plain_10, TEXT_ALIGN_LEFT);
  // delay(100);
}
void btnEvent_Service()
{
  switch (KeyCode)
  {
  case keyA:
    patch_data_button_db("btnA");
    refresh_btnCode_lcd("btnA");
    break;
  case keyB:
    patch_data_button_db("btnB");
    refresh_btnCode_lcd("btnB");
    break;
  case keyC:
    patch_data_button_db("btnC");
    refresh_btnCode_lcd("btnC");
    break;
  case keyD:
    patch_data_button_db("btnD");
    refresh_btnCode_lcd("btnD");
    break;
  case keyE:
    patch_data_button_db("btnE");
    refresh_btnCode_lcd("btnE");
    break;
  case keySetup:
    Heltec.display->clear();
    Heltec.display->setColor(WHITE);
    showText(0, 0, "Go to setup esp");
    delay(200);
    indruino.myRom()->writeChar(Rom_check_data, 0x00);
    ESP.restart();
    break;
  default:
    break;
  }
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
void wifi_icon()
{
  Heltec.display->drawXbm(40, 0, WIFI_width, WIFI_height, WIFI_bits);
  Heltec.display->display();
}
void enableTimerTick(timerTick_ &timer)
{
  timer.run = true;
  // timer.time_delay = time_set_clear;
  timer.last_value = millis();
}
void send_ok_lcd()
{
  Heltec.display->setColor(BLACK);
  Heltec.display->drawString(60, 0, "Error");
  Heltec.display->setColor(WHITE);
  Heltec.display->drawString(60, 0, "OK");
  Heltec.display->display();
  enableTimerTick();
}
void send_error_lcd()
{
  Heltec.display->setColor(BLACK);
  Heltec.display->drawString(60, 0, "OK");
  Heltec.display->setColor(WHITE);
  Heltec.display->drawString(60, 0, "Error");
  Heltec.display->display();
  enableTimerTick();
}
void clear_send_status_lcd()
{
  Heltec.display->setColor(BLACK);
  Heltec.display->drawString(60, 0, "Error");
  Heltec.display->drawString(60, 0, "OK");
  Heltec.display->display();
}
void check_clear_status_lcd(timerTick_ &timer)
{
  if (timer.run == true)
  {
    timer.curr_value = millis();
    if (timer.curr_value - timer.last_value > timer.time_delay)
    {
      clear_send_status_lcd();
      timer.run = false; //disnable
    }
  }
}
void refresh_product_code_lcd(char *data)
{
  Heltec.display->setColor(BLACK);
  Heltec.display->fillRect(0, 12, 128, 12);
  Heltec.display->setColor(WHITE);
  showText(0, 12, data);
  Heltec.display->display();
}
void check_new_product_code(timerTick_ &timer)
{
  if (timer.run == false)
  {
    timer.last_value = millis();
    timer.run = true;
  }
  if (timer.run == true)
  {
    timer.curr_value = millis();
    if (timer.curr_value - timer.last_value > timer.time_delay)
    {
      char *pch = get_data_db(ID_board);
      decodeJson(pch);
      timer.run = false;
    }
  }
}
void initLCD()
{
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->clear();
}

void refresh_btnCode_lcd(char *data)
{
  Heltec.display->setColor(BLACK);
  Heltec.display->fillRect(0, 24, 128, 12);
  Heltec.display->setColor(WHITE);
  showText(0, 24, data);
  Heltec.display->display();
  enableTimer_databtn();
}
void enableTimer_databtn(timerTick_ &timer)
{
  timer.run = true;
  // timer.time_delay = time_clear_btnCode;
  timer.last_value = millis();
}
void clear_btnCode_lcd()
{
  //clear lcd line
  Heltec.display->setColor(BLACK);
  Heltec.display->fillRect(0, 24, 128, 12);
  Heltec.display->display();
}
void check_clear_btnCode_lcd(timerTick_ &timer)
{
  if (timer.run == true)
  {
    timer.curr_value = millis();
    if (timer.curr_value - timer.last_value > timer.time_delay)
    {
      clear_btnCode_lcd();
      timer.run = false; //disnable
    }
  }
}

void connect_wifi()
{
  // showText(0, 16, "Connecting...");
  WiFi.begin(ssid.c_str(), pass.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Heltec.display->setColor(INVERSE);
    wifi_icon();
    delay(500);

    buttonAlive();
    check_btn_press();
    if (KeyCode == keySetup)
    {
      //showText(0, 30, "Setup");
    }
#ifdef SerialDebug
    Serial.print(".");
#endif
  }
  Heltec.display->setColor(WHITE);
  wifi_icon();

#ifdef SerialDebug
  Serial.println(WiFi.localIP());
#endif
}

//db
char *get_data_db(const char *data) //get data productCode
{
  String _reData = "";
  if ((WiFi.status() == WL_CONNECTED))
  {
    WiFiClient client;
    HTTPClient http;
    String page = String(url_service);
    page += "/";
    page += String(ID_board);
#ifdef SerialDebug
    Serial.println(page);
#endif
    http.begin(client, page);
    int httpCode = http.GET();
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_NOT_FOUND)
      {

        http.end();
        return "";
      }
      else if (httpCode == HTTP_CODE_OK)
      {
        int len = http.getSize();
        _reData = http.getString();

#ifdef SerialDebug
        Serial.println();
        Serial.print("respond: ");
        Serial.println(_reData);
#endif
        //if ton tai Not found => ""
        http.end();
        send_ok_lcd();
        return (char *)_reData.c_str();
      }
      else //httpCode not OK
      {
        send_error_lcd();
        http.end();
        return "";
      }
    }
    else // httpCode <=0
    {
      send_error_lcd();
      return "";
    }

    //decodeJson(_reData);

    //**return (char *)_reData.c_str();
    //http.end();
  }
  else
  {
    //heltec blink wifi
    send_error_lcd();
    return "";
  }
}
bool patch_data_button_db(char *data)
{
  String _reData = "";
  String postPatchData = "";
  if ((WiFi.status() == WL_CONNECTED))
  {
    WiFiClient client;
    HTTPClient http;
    String page = String(url_service);
    page += "/";
    page += String(ID_board);
    http.begin(client, page);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    postPatchData = "dButtonCode=" + String(data);
    postPatchData += "&isNewButton=true";

    int httpCode = http.sendRequest("PUT", postPatchData);
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_NOT_FOUND)
      {
        http.end();
        send_error_lcd();
        return false;
      }
      else if (httpCode == HTTP_CODE_OK)
      {
        int len = http.getSize();
        String payload = http.getString();
#ifdef SerialDebug
        Serial.println(payload);
#endif
        http.end();
        send_ok_lcd();
        return true;
      }
      else // http not ok
      {
        //print lcd
        send_error_lcd();
        //print lcd
        return false;
      }
    }
    else // http code <=0
    {
      //print lcd
      send_error_lcd();
      //print lcd
      return false;
    }
  }
}
//db
//json
void decodeJson(String &data)
{
  if (data.length() <= 1)
    return;
  static size_t capacity = JSON_OBJECT_SIZE(8) + 267;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, data);
  const char *ProductOrtherCode = doc["ProductOrtherCode"];
#ifdef SerialDebug
  Serial.println(String(ProductOrtherCode));
#endif
  if (strcmp(last_ProductOrtherCode, ProductOrtherCode) != 0)
  {
    memcpy(last_ProductOrtherCode, ProductOrtherCode, sizeof(ProductOrtherCode));
    refresh_product_code_lcd((char *)ProductOrtherCode);
  }
  //test
  doc.clear();
  //test
}
void decodeJson(char *_data)
{
  if (strlen(_data) <= 1)
    return;
  static size_t capacity = JSON_OBJECT_SIZE(8) + 267;
  DynamicJsonDocument doc(capacity);
  deserializeJson(doc, _data);
  const char *ProductOrtherCode = doc["ProductOrtherCode"];
#ifdef SerialDebug
  Serial.println(String(ProductOrtherCode));
#endif
  if (strcmp(last_ProductOrtherCode, ProductOrtherCode) != 0)
  {
    memcpy(last_ProductOrtherCode, ProductOrtherCode, sizeof(ProductOrtherCode));
    refresh_product_code_lcd((char *)ProductOrtherCode);
  }
  //test
  doc.clear();
  //test
}
//

//fix sau
bool do_import_data_barcode(char *data)
{
  String _reData = "";
  String postPatchData = "";
  if ((WiFi.status() == WL_CONNECTED))
  {
    WiFiClient client;
    HTTPClient http;
    String page = String(url_service);
    page += "/";
    page += String(ID_board);
    http.begin(client, page);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    postPatchData += "dBarcodeCode=" + String(data);
    postPatchData += "&isNewBarcode=true";

    int httpCode = http.sendRequest("PUT", postPatchData);
    if (httpCode > 0)
    {
      if (httpCode == HTTP_CODE_NOT_FOUND)
      {
        http.end();
        send_error_lcd();
        return false;
      }
      else if (httpCode == HTTP_CODE_OK)
      {
        int len = http.getSize();
        String payload = http.getString();
#ifdef SerialDebug
        Serial.println(payload);
#endif
        http.end();
        send_ok_lcd();
        return true;
      }
      else // http not ok
      {
        //print lcd
        send_error_lcd();
        //print lcd
        return false;
      }
    }
    else // http code <=0
    {
      //print lcd
      send_error_lcd();
      //print lcd
      return false;
    }
  }
}
//fix sau