unsigned long lastTime=0;

uint16_t readAnalog(int pinAnalog, unsigned long delayms){
  unsigned long endTime = millis();
  if(endTime - lastTime > delayms){
    return(analogRead(pinAnalog));
    lastTime = endTime;
  }
}

void setup() {

}

void loop() {
  
}
