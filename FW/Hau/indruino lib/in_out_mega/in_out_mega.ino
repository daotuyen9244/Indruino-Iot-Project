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

unsigned int au16data[50] = {0};

void setup() {

   DDRC = 0x00;
   PORTC = 0xFF;
   DDRA = 0xFF;
   PORTA = 0x00;
  

  modbus_configure(&Serial, 9600, 1, 7, 100, au16data);
  
  
  cv_data.uint_arr  = au16data;
  
  // put your setup code here, to run once:
 
}

byte last_value_out = 0x00;
byte last_value_in = 0x00;
void loop() {

  modbus_update();
  
  //Serial.println(PINC);
  if(cv_data.byte_arr[Ram_OUT_P] != last_value_out)
  {
    
     PORTA = cv_data.byte_arr[Ram_OUT_P];
     last_value_out = cv_data.byte_arr[Ram_OUT_P];
  }

  if((cv_data.byte_arr[Ram_IN_P] != last_value_in))
  {
    // cv_data.byte_arr[Ram_IN_P] = PINC;
    // last_value_in = PINC;
  }

  // if(PINC != last_value_in)
  // {
  //   PORTA = PINC;
  //   last_value_out = PINC;
  //   last_value_in = PINC;
  // }
  // put your main code here, to run repeatedly:

}
