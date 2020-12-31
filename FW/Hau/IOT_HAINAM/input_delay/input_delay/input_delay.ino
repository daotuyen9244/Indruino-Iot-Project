
unsigned long last_time = 0;
bool readInputDigital(uint8_t pinRead, unsigned long time_delay, bool active);
void setup() {
  // put your setup code here, to run once:
  pinMode(9, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  readInputDigital(9, 1000, LOW);

}

bool readInputDigital(uint8_t pinRead, unsigned long time_delay, bool active)
{
  if (digitalRead(pinRead) == active)
  {
    if (millis() - last_time > time_delay)
    {
      if (digitalRead(pinRead) == active)
      {
        Serial.println("ok");
        last_time = millis();
      }
    }
  }
}
