#include "indruino_data.h"

Indruino::Indruino()
{
}
Indruino::~Indruino()
{
}

void Indruino::init()
{
    if (_rom == nullptr)
        _rom = &rom;
    if (_ram == nullptr)
        _ram = &ram;
    if (_synData == nullptr)
        _synData = &synData;
    _ram->init(_SIZE_OF_RAM);
    _rom->init();
    _synData->init();
}
ROM *Indruino::myRom()
{
    return _rom;
}
SRAM *Indruino::myRam()
{
    return _ram;
}
SRAM *Indruino::myRam(int pos)
{
    if(pos >= count_ram) return false;
    return _ram + pos;
}

int Indruino::count_Ram(void) {
    return count_ram;    
}

int Indruino::now_Ram_choose(void) {
    return now_pos;    
}

void Indruino::createNewRam(int size) {
  //  _ram+count_ram-1    
}
