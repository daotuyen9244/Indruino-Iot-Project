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
    RamEeprom *_synData = nullptr;
    int now_pos = 0;
    int count_ram = 1;
public:
    void init();
    
    //ROM function
    ROM *myRom(); //return ptr of ram
    //ROM function

    //SRAM function
    SRAM *myRam(int pos); //default pos = 0
    SRAM *myRam(void);
    int count_Ram(void);
    int now_Ram_choose(void);
    void createNewRam(int size);
    void deleteRam(int pos);
    bool setNowPos(int pos);
    //SRAM function



    RamEeprom *synMyData(void);
    RamEeprom *synMyData(SRAM *ptr_ram);
    Indruino();
    ~Indruino();
};





#endif //_INDRUINO_DATA