#include <EEPROM.h>
void setup() {
  // put your setup code here, to run once:

  EEPROM.begin(1024);

  for(uint16_t count = 0; count  < 1024; count++)
  {
    EEPROM.write(count, 1);
    EEPROM.commit();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
