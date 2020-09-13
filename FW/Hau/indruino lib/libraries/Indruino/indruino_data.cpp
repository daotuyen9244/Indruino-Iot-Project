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
    _new_Ram = new SRAM[_SIZE_MAX_NEW_RAM];
}
ROM *Indruino::myRom()
{
    return _rom;
}
SRAM *Indruino::myRam()
{
    if (_now_pos > _count_ram)
        return nullptr;
    if (_now_pos < 0)
        return nullptr;
    if (_now_pos == 0)
        return _ram;
    //else
    return _new_Ram + _now_pos - 1;
}
SRAM *Indruino::myRam(int pos) //0 1 2
{
    if (pos > _count_ram)
        return nullptr;
    if (pos < 0)
        return nullptr;
    if (pos == 0)
        return _ram;
    //else
    return _new_Ram + pos - 1;
}

int Indruino::count_Ram(void)
{
    return _count_ram;
}

int Indruino::now_Ram_choose(void)
{
    return _now_pos;
}
RamEeprom *Indruino::synMyData(void) //use _ram default for syn if _now_pos == 0;
{
    if (_now_pos == 0)
    {
        _synData->setRam(*_ram);
    }
    if (_now_pos != 0)
    {
        _synData->setRam(*(_new_Ram + _now_pos - 1));
    }
    return _synData;
}

RamEeprom *Indruino::synMyData(int pos) //use _ram default for syn if _now_pos == 0;
{
    if (pos == 0)
    {
        _synData->setRam(*_ram);
    }
    if (pos != 0)
    {
        _synData->setRam(*(_new_Ram + pos - 1));
    }
    return _synData;
}

void Indruino::createNewRam(int size, int pos) //pos 1 2 - > < max_size_new_RAM
{
    if (pos >= _SIZE_MAX_NEW_RAM)
        return;
    if ((size > _SIZE_OF_RAM) || (size < 0))
        return;
    SRAM *_ram_ptr = (_new_Ram + pos - 1);
    _ram_ptr->init(size);
    _count_ram++;
}
void Indruino::deleteRam(int pos)
{
    if ((pos > _count_ram) || (pos <= 0))
        return;
    SRAM *_ram_ptr = _new_Ram + pos - 1;
    _ram_ptr->~SRAM();
    _count_ram--;
}

bool Indruino::setNowPos(int pos)
{
    if (pos < 0 || pos >= _SIZE_MAX_NEW_RAM)
        return false;
    _now_pos = pos;
    return true;
}
