#include "indruino_data.h"

Indruino indruino;
void setup()
{
    Serial.begin(9600);
    while(!Serial);

    indruino.init(); //initialize the indruino object
    int address_ram = 0;
    uint8_t value_ram = 12;
    indruino.myRam()->writeByte(address_ram, value_ram);
    
    Serial.print("value at addr" + String(address_ram) + "= ");
    Serial.println(indruino.myRam()->readByte(address_ram));

    int address_rom = 0;
    uint8_t value_rom = 18;
    Serial.println(indruino.myRom()->readByte(address_rom)); //read now byte value in you rom;
    
    indruino.myRom()->writeByte(address_rom, value_rom);
    Serial.println(indruino.myRom()->readByte(address_rom)); //now your value at addr address_rom was changed to value_rom
    
    indruino.synMyData()->write2RamByte(address_ram, address_rom);

    Serial.println(indruino.myRam()->readByte(address_ram)); //read now value of ram at address_ram

}
void loop()
{

}