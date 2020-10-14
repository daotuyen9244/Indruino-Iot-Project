//#include "indruino_data.h"
#include "SimpleModbusSlave_DUE.h"
#include "config_addr.h"
#define ID 1

typedef union convert
{
  byte *byte_arr;
  unsigned int *uint_arr;
} CONVERT;

CONVERT cv_data;


typedef union cva
{
  byte temp[2];
  uint16_t data = 0;
} CVA;
CVA data_analog;

unsigned int au16data[50] = {0};

byte buttonState;           // the current reading from the input pin
byte lastButtonState = LOW; // the previous reading from the input pin

unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;

void setup()
{

  DDRC = 0x00;
  PORTC = 0xFF;
  DDRA = 0xFF;
  PORTA = 0x00;

  pinMode(A0, INPUT);
  
  modbus_configure(&Serial, 9600, 1, 255, 50, au16data);

  cv_data.uint_arr = au16data;

  // put your setup code here, to run once:
  //Serial.begin(9600);
}

byte last_value_out = 0x00;
byte last_value_in = 0x00;
byte value_out = 0x00;
byte i = 0;
unsigned long last_value = 0;




void loop()
{

  modbus_update();
  data_analog.data = analogRead(A0);
  //Serial.println(analogRead(A0));

  cv_data.byte_arr[Ram_ADC0] = data_analog.temp[0];
  cv_data.byte_arr[Ram_ADC0 + 1] = data_analog.temp[1];
  //analog read
  

  //debounce
  if (PINC != last_value_in)
  {
    last_value = millis();
  }

  if (millis() - last_value > 50)
  {
    last_value_in = PINC;
    if (PINC != 0x00)
    {
      PORTA = (cv_data.byte_arr[Ram_OUT_P] | PINC);
    }
    else
    {
      PORTA = cv_data.byte_arr[Ram_OUT_P];
    }
  }

  //out put
  if(PINC == 0x00)
  {
    PORTA = cv_data.byte_arr[Ram_OUT_P];
  }
  last_value_in = PINC;
  cv_data.byte_arr[Ram_IN_P] = PORTA;

  
  // last_value = millis();
  //}

  // last_value_in = PINC;
  // }
  // put your main code here, to run repeatedly:
}
