#ifndef _INDRUINO_DATA
#define _INDRUINO_DATA

#include <Arduino.h>
#include "config_mem.h"
#include "SRAM_cus.h"
#include "ROM.h"
#include "ram_eeprom.h"

#define _SIZE_MAX_NEW_RAM 3

class Indruino
{
private:
    SRAM *_new_Ram; //you can create new ram if you want max is 3
    SRAM *_ram = nullptr; //default
    ROM *_rom =nullptr;
    RamEeprom *_synData = nullptr; //default
    int _now_pos = 0;
    int _count_ram = 0; //count new raw
public:
    void init();
    
    //ROM function
    ROM *myRom(); //return ptr of ram
    //ROM function

    //SRAM function
    SRAM *myRam(int pos); //default pos = 0
    SRAM *myRam(void); //return ram default
    int count_Ram(void);
    int now_Ram_choose(void);
    void createNewRam(int size, int pos);
    void deleteRam(int pos);
    bool setNowPos(int pos);
    //SRAM function


    RamEeprom *synMyData(int pos); 
    RamEeprom *synMyData(void);
    Indruino();
    ~Indruino();
};





#endif //_INDRUINO_DATA