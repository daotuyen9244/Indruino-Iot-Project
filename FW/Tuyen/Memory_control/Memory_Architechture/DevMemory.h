#include "Arduino.h"
#define USE_EPPROM
#define USE_ExI2C
#define ESP32
#define R8BIT 32
#define R16BIT 32
#define R32BIT 20    // float memory
#define RFLOAT 20    // float memory
#define RDBL 10     // long memory
#define ADD_LENS R8BIT
#ifdef USE_EPPROM

#ifdef USE_ExI2C
#include <Wire.h>
#include <Eeprom24C32_64.h>
#define I2CEEPROM_ADDRESS 0x57
#define ExSDA 4
#define ExSCL 15
static Eeprom24C32_64 eeprom(I2CEEPROM_ADDRESS);
#endif

#include "EEPROM.h"
#define EEPROM_SIZE 512
#define EUCHAR 32
#define ECHAR 32
#define EUINT 32
#define EINT 32
#define EUINT32 20
#define EINT32 20 
#define EFLOAT 20   // float memory
#define EDBL 10     // long memory

#define EUCHAR_START 0
#define ECHAR_START (EUCHAR_START+EUCHAR)
#define EUINT_START (ECHAR_START+ECHAR)
#define EINT_START (EUINT_START+EUINT)
#define EUINT32_START (EINT_START+EINT)
#define EINT32_START (EUINT32_START+EUINT32)
#define EFLOAT_START (EINT32_START+EINT32)
#define EDBL_START (EFLOAT_START + EFLOAT)
#endif
static unsigned char _maxIn =1;
static unsigned char _maxOut =1;

static unsigned char _InputStart =0;
static unsigned char _OutputStart =_maxIn+1;

struct DevMemoryMap
{
   unsigned char DevUChar[R8BIT];
   char DevChar[R8BIT];

   uint16_t DevUInt[R16BIT];
   int16_t DevInt[R16BIT];

   uint32_t DevUInt32[R32BIT];
   int32_t DevInt32[R32BIT];

   float DevFloat[RFLOAT];
   double DevDouble[RDBL];
} ; 
static DevMemoryMap MemMap;
class DevMemory
{
public:
    
    void write_ram_Block(unsigned char add, unsigned int lens,unsigned char *data);
    unsigned char read_ram_Block(unsigned char add, unsigned int lens,unsigned char *data);

    
    void write_ram_UChar(unsigned char add, unsigned char data);
    unsigned char read_ram_UChar(unsigned char add);

    void write_ram_Char(unsigned char add, char data);
    char read_ram_Char(unsigned char add);

    void write_ram_UInt(unsigned char add, unsigned int data);
    unsigned int read_ram_UInt(unsigned char add);

    void write_ram_Int(unsigned char add, int data);
    int read_ram_Int(unsigned char add);

    void write_ram_UInt32(unsigned char add, unsigned long data);
    unsigned long read_ram_UInt32(unsigned char add);

    void write_ram_Int32(unsigned char add, long data);
    long read_ram_Int32(unsigned char add);

    void write_ram_Float(unsigned char add, float data);
    float read_ram_Float(unsigned char add);

    void write_ram_Double(unsigned char add, double data);
    double read_ram_Double(unsigned char add);

    bool setOutputAdd(unsigned char add,unsigned char lens);
    bool setInputAdd(unsigned char add,unsigned char lens);

    unsigned char InputAddBegin();
    unsigned char OutputAddBegin();

    unsigned char InputLens();
    unsigned char OutputLens();

    unsigned char ReadInPut(unsigned char add);
    unsigned char ReadOutPut(unsigned char add);
    bool WriteOutPut(unsigned char add,unsigned char data);
#ifdef USE_EPPROM
    bool initEPPROM();
    unsigned char readEPPROM(unsigned char add);
    bool writeEPPROM(unsigned char add,unsigned char data);
    void saveEPPROM();
    void write_rom_UChar(unsigned char add, unsigned char data);
    unsigned char read_rom_UChar(unsigned char add);

    void write_rom_Char(unsigned char add, char data);
    char read_rom_Char(unsigned char add);

    void write_rom_UInt(unsigned char add, unsigned int data);
    unsigned int read_rom_UInt(unsigned char add);

    void write_rom_Int(unsigned char add, int data);
    int read_rom_Int(unsigned char add);

    void write_rom_UInt32(unsigned char add, unsigned long data);
    unsigned long read_rom_UInt32(unsigned char add);

    void write_rom_Int32(unsigned char add, long data);
    long read_rom_Int32(unsigned char add);

    void write_rom_Float(unsigned char add, float data);
    float read_rom_Float(unsigned char add);

    void write_rom_Double(unsigned char add, double data);
    double read_rom_Double(unsigned char add);
    
    void copy_rom_to_ram_UChar(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_UChar(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Char(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Char(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_UInt(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Uint(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Int(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_int(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_UInt32(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_UInt32(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Int32(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Int32(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_ULong(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_ULong(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Long(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Long(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Float(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Float(unsigned char fadd,unsigned char radd);

    void copy_rom_to_ram_Double(unsigned char radd,unsigned char fadd);
    void copy_ram_to_rom_Double(unsigned char fadd,unsigned char radd);

    void write_rom_Block(unsigned char add, unsigned int lens,unsigned char *data);
    unsigned char read_rom_Block(unsigned char add, unsigned int lens,unsigned char *data);
    #ifdef USE_ExI2C
    bool initI2CEPPROM();
    unsigned char readI2C_rom(unsigned char add);
    bool writeI2C_rom(unsigned char add,unsigned char data);
    void write_I2C_rom_UChar(unsigned char add, unsigned char data);
    unsigned char read_I2C_rom_UChar(unsigned char add);

    void write_I2C_rom_Char(unsigned char add, char data);
    char read_I2C_rom_Char(unsigned char add);

    void write_I2C_rom_UInt(unsigned char add, unsigned int data);
    unsigned int read_I2C_rom_UInt(unsigned char add);

    void write_I2C_rom_Int(unsigned char add, int data);
    int read_I2C_rom_Int(unsigned char add);

    void write_I2C_rom_UInt32(unsigned char add, unsigned long data);
    unsigned long read_I2C_rom_UInt32(unsigned char add);

    void write_I2C_rom_Int32(unsigned char add, long data);
    long read_I2C_rom_Int32(unsigned char add);

    void write_I2C_rom_Float(unsigned char add, float data);
    float read_I2C_rom_Float(unsigned char add);

    void write_I2C_rom_Double(unsigned char add, double data);
    double read_I2C_rom_Double(unsigned char add);
    
    void copy_I2C_rom_to_ram_UChar(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_UChar(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Char(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Char(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_UInt(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Uint(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Int(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_int(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_UInt32(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_UInt32(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Int32(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Int32(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_ULong(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_ULong(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Long(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Long(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Float(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Float(unsigned char fadd,unsigned char radd);

    void copy_I2C_rom_to_ram_Double(unsigned char radd,unsigned char fadd);
    void copy_ram_to_I2C_rom_Double(unsigned char fadd,unsigned char radd);

    void write_I2C_rom_Block(unsigned char add, unsigned int lens,unsigned char *data);
    unsigned char read_I2C_rom_Block(unsigned char add, unsigned int lens,unsigned char *data);
    #endif
#endif
private:
protected:
};
