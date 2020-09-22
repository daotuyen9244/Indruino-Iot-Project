#ifndef _CONFIG_MEM_H
#define _CONFIG_MEM_H

#define NOESP32 //if your board is ESP32 or ESP8266, you need this define


// //**config size and postion of eeprom**//
#define _SIZE_OF_EEPROM 512 //max is 512
const uint8_t Eeprom_value[_SIZE_OF_EEPROM] = {0}; //config position
// //**config size and postion of eeprom **//



// //**config size and postion of ram **//
#define _SIZE_OF_RAM 512
const uint8_t Ram_value[_SIZE_OF_RAM] = {0}; //data postion
// //**config size and postion of ram **//


#endif //_CONFIG_MEM_H