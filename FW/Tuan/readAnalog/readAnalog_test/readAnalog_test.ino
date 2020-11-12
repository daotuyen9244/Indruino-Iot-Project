unsigned long lastTime=0;
unsigned long delay1s=0;
uint16_t readAnalog(byte pinAnalog, unsigned long delayms){
  unsigned long endTime = millis();
  if(endTime - lastTime >= delayms){
    lastTime = endTime;
    return analogRead(pinAnalog); }
}
void setup() {
  Serial.begin(9600);
}
void loop() {
  unsigned long endTime = millis();
  if(endTime - delay1s >= 2000){
    Serial.print("Doc truc tiep: ");
    Serial.println(analogRead(13));
    Serial.print("Doc qua ham: ");
    Serial.println(readAnalog(13,2000));
    delay1s = endTime;
  }
}
