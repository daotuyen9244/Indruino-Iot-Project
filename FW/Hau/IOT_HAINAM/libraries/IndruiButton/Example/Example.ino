#include <IndruiButton.h>

IndruiButton Left(34);
int count = 0;
void setup(){
  Serial.begin(115200);
  Left.setDebounceTime(50);
}
void loop(){
  Left.loop();
  if(Left.isPressed())
  {
    Serial.println("The button left is pressed");
  }
}
