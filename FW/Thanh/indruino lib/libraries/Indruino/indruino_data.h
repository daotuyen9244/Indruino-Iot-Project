#ifndef _INDRUINO_DATA
#define _INDRUINO_DATA

#include <Arduino.h>
#include "config_mem.h"
#include "SRAM_cus.h"
#include "ROM.h"
#include "ram_eeprom.h"


class Indruino
{
private:
    SRAM *_ram = nullptr; //you can create new ram if you want
    ROM *_rom =nullptr;
public:
    void init();
    ROM *myRom();
    SRAM *myRam(SRAM *_ptr_ram);
    SRAM *myRam(void);
    RamEeprom *syn(void);
    Indruino();
    ~Indruino();
};





#endif //_INDRUINO_DATA