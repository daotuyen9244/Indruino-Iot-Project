
unsigned long last_time = 0;
uint16_t readInputAnalog(uint8_t pinRead, unsigned long time_delay);
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readInputAnalog(9, 1000);
}

uint16_t readInputAnalog(uint8_t pinRead, unsigned long time_delay)
{
    if (millis() - last_time > time_delay)
    {
        last_time = millis();
        return analogRead(pinRead);
    }
}
