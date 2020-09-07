//**This is a lib which support for write another type of date**

//updated in future choose add of ram data array before your progress

#ifndef _RAMEEPROM_H
#define _RAMEEPROM_H
#include <Arduino.h>

#include "SRAM_cus.h"
#include "ROM.h"
//syn data between ram && rom
class RamEeprom
{
private:
    SRAM *p_ram = nullptr; //with only one ram I was created recently
    ROM *p_rom = nullptr;

public:
    RamEeprom();
    ~RamEeprom();

    void init();
    void setRam(SRAM &p_ram_arr);
    void resetRam();

    //writetoRomWithChooseSRAM
    bool write2RomByte(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomChar(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomUChar(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomShort(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomUShort(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomInt(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomUInt(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomLong(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomULong(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomLong64(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomULong64(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomFloat(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomDouble(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomBool(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomString(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RomString(int addRom, int addRam, int len, SRAM *p_ram_arr);
    bool write2RomBytes(int addRom, int addRam, int len, SRAM *p_ram_arr);
    template <class T>
    bool write2RomAll(int addRom, int addRam, const T &value, SRAM *p_ram_arr); //write data at add with len and write it to *p
    template <class T>
    bool write2RomAll(int addRom, int addRam, uint16_t len, const T &value, SRAM *p_ram_arr); //n byte
    //writetoRomWithChooseSRAM

    //writetoRom
    bool write2RomByte(int addRom, int addRam);
    bool write2RomChar(int addRom, int addRam);
    bool write2RomUChar(int addRom, int addRam);
    bool write2RomShort(int addRom, int addRam);
    bool write2RomUShort(int addRom, int addRam);
    bool write2RomInt(int addRom, int addRam);
    bool write2RomUInt(int addRom, int addRam);
    bool write2RomLong(int addRom, int addRam);
    bool write2RomULong(int addRom, int addRam);
    bool write2RomLong64(int addRom, int addRam);
    bool write2RomULong64(int addRom, int addRam);
    bool write2RomFloat(int addRom, int addRam);
    bool write2RomDouble(int addRom, int addRam);
    bool write2RomBool(int addRom, int addRam);
    bool write2RomString(int addRom, int addRam);
    bool write2RomString(int addRom, int addRam, int len);
    bool write2RomBytes(int addRom, int addRam, int len);
    // template <class T>
    // bool write2RomAll(int addRom, int addRam, const T &value); //write data at add with len and write it to *p
    // template <class T>
    // bool write2RomAll(int addRom, int addRam, uint16_t len, const T &value);
    //writetoRom

    //chua edit
    //writeRam choose SRAM
    bool write2RamByte(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamChar(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamUChar(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamShort(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamUShort(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamInt(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamUInt(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamLong(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamULong(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamLong64(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamULong64(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamFloat(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamDouble(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamBool(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamString(int addRom, int addRam, SRAM *p_ram_arr);
    bool write2RamString(int addRom, int addRam, int len, SRAM *p_ram_arr);
    bool write2RamBytes(int addRom, int addRam, int len, SRAM *p_ram_arr);
    template <class T>
    bool write2RamAll(int addRom, int addRam, const T &value, SRAM *p_ram_arr); //write data at add with len and write it to *p
    template <class T>
    bool write2RamAll(int addRom, int addRam, uint16_t len, const T &value, SRAM *p_ram_arr); //n byte
    // template <class T>
    // bool write2RamAll(uint16_t add, T &value); //write data at add with len and write it to *p
    // template <class T>
    // bool write2RamAll(uint16_t add, uint8_t *ptr_value, uint16_t len);
    //writeRam choose SRAM

    //writeRam
    bool write2RamByte(int addRom, int addRam);
    bool write2RamChar(int addRom, int addRam);
    bool write2RamUChar(int addRom, int addRam);
    bool write2RamShort(int addRom, int addRam);
    bool write2RamUShort(int addRom, int addRam);
    bool write2RamInt(int addRom, int addRam);
    bool write2RamUInt(int addRom, int addRam);
    bool write2RamLong(int addRom, int addRam);
    bool write2RamULong(int addRom, int addRam);
    bool write2RamLong64(int addRom, int addRam);
    bool write2RamULong64(int addRom, int addRam);
    bool write2RamFloat(int addRom, int addRam);
    bool write2RamDouble(int addRom, int addRam);
    bool write2RamBool(int addRom, int addRam);
    bool write2RamString(int addRom, int addRam);
    bool write2RamString(int addRom, int addRam, int len);
    bool write2RamBytes(int addRom, int addRam, int len);
    //writeRam

    //syn
    bool loadRam2Rom(int addRom, int addRam, int lenRam,SRAM *p_ram_arr);
    bool loadRam2Rom(int addRom, int addRam, SRAM *p_ram_arr);

    bool loadRom2Ram(int addRom, int addRam, int lenRom,SRAM *p_ram_arr);
    bool loadRom2Ram(int addRom, int addRam, SRAM *p_ram_arr);
    
    //function dong bo ram and rom(load ram) - (load rom) ..etc

    //syn
};
//syn data between ram && rom
#endif //_RAMEEPROM_H