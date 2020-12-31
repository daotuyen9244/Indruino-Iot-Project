#ifndef BUTTON_FUNCTION_H
#define BUTTON_FUNCTION_H

#include "IndruiButton.h"
//KeyCode
#define keyA 0x01
#define keyB 0x02
#define keyC 0x04
#define keyD 0x08
#define keyE 0x10
#define keySetup 0x03 //btnA and btn B


//define for button
#define Left 38
#define Right 37
#define Up 34
#define Down 39
#define Enter 36
#define debounce_time 50
IndruiButton btnA(Left);
IndruiButton btnB(Up);
IndruiButton btnC(Down);
IndruiButton btnD(Right);
IndruiButton btnE(Enter);
//define for button

void setupButton();
void buttonAlive();
void btnA_Acction_press();
void btnB_Acction_press();
void btnC_Acction_press();
void btnD_Acction_press();
void btnE_Acction_press();
void check_btn_press();

int8_t KeyCode = 0;

void setupButton()
{
  btnA.setDebounceTime(debounce_time);
  btnB.setDebounceTime(debounce_time);
  btnC.setDebounceTime(debounce_time);
  btnD.setDebounceTime(debounce_time);
  btnE.setDebounceTime(debounce_time);
}
void buttonAlive()
{
  btnA.loop();
  btnB.loop();
  btnC.loop();
  btnD.loop();
  btnE.loop();
}
void btnA_Acction_press()
{
  if (btnA.isPressed())
  {
    KeyCode |=keyA;
    // patch_data_button_db("btnA");
    // refresh_btnCode_lcd("btnA");
  }
  else
  {
      KeyCode &=~keyA;
  }
  
}
void btnB_Acction_press()
{
  if (btnB.isPressed())
  {
    KeyCode |=keyB;

    // patch_data_button_db("btnB");
    // refresh_btnCode_lcd("btnB");
  }
  else
  {
      KeyCode &=~keyB;
  }
  
}
void btnC_Acction_press()
{
  if (btnC.isPressed())
  {
      KeyCode |=keyC;
    // patch_data_button_db("btnC");
    // refresh_btnCode_lcd("btnC");
  }
  else
  {
      KeyCode &=~keyC;
  }
  
}
void btnD_Acction_press()
{
  if (btnD.isPressed())
  {
      KeyCode |=keyD;
    // patch_data_button_db("btnD");
    // refresh_btnCode_lcd("btnD");
  }
  else
  {
      KeyCode &=~keyD;
  }
  
}
void btnE_Acction_press()
{
  if (btnE.isPressed())
  {
      KeyCode |=keyE;
    // patch_data_button_db("btnE");
    // refresh_btnCode_lcd("btnE");
  }
  else
  {
      KeyCode &=~keyE;
  }
  
}
void check_btn_press()
{
  btnA_Acction_press();
  btnB_Acction_press();
  btnC_Acction_press();
  btnD_Acction_press();
  btnE_Acction_press();
  
}

#endif