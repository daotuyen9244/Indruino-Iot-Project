#include "Arduino.h"
#define USE_EPPROM
#define USE_ExI2C
#define ESP32
#define RAM_SIZE 1024
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
#define EEPROM_SIZE 1024
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
   //uint8_t Data[RAM_SIZE];
   //uint8_t DevMCommon[2*R8BIT + 2*R16BIT +2*R32BIT+RFLOAT+RDBL];
} ; 


static DevMemoryMap MemMap;
//static uint8_t *CData = (uint8_t*)&MemMap;
static uint8_t *CData ;
template <class T> 
int write_ram(uint8_t *D,int add, const T& value)
{
   const uint8_t* p = (const uint8_t*)(const void*)&value;
   int i;
   for (i = 0; i < sizeof(value); i++)
   {
     *(D+add+i) = *p++;
   }
   return i;
}

template <class T> 
int read_ram(uint8_t *D,int add, T& value)
{
   uint8_t* p = (uint8_t*)(void*)&value;
   int i;
   for (i = 0; i < sizeof(value); i++)
   {
     *p++ = D[add+i];
   }
       //*p++ = addPROM.read(add++);
   return i;
}

static void setAddPointer(DevMemoryMap &S)
{
  //CData=(uint8_t*)&(S.DevUChar[0]);
  CData=(uint8_t*)&S;
}
class DevMemory
{
public:
    
    void write_ram_Block(uint16_t add, unsigned int lens,unsigned char *data);
    unsigned char read_ram_Block(uint16_t add, unsigned int lens,unsigned char *data);
    
    
    void write_ram_UChar(uint16_t add, unsigned char data);
    unsigned char read_ram_UChar(uint16_t add);
    
    void write_ram_Char(uint16_t add, char data);
    char read_ram_Char(uint16_t add);

    void write_ram_UInt(uint16_t add, unsigned int data);
    unsigned int read_ram_UInt(uint16_t add);

    void write_ram_Int(uint16_t add, int data);
    int read_ram_Int(uint16_t add);

    void write_ram_UInt32(uint16_t add, unsigned long data);
    unsigned long read_ram_UInt32(uint16_t add);

    void write_ram_Int32(uint16_t add, long data);
    long read_ram_Int32(uint16_t add);

    void write_ram_Float(uint16_t add, float data);
    float read_ram_Float(uint16_t add);

    void write_ram_Double(uint16_t add, double data);
    double read_ram_Double(uint16_t add);
    bool setOutputAdd(uint16_t add,unsigned char lens);
    bool setInputAdd(uint16_t add,unsigned char lens);
    
    unsigned char InputAddBegin();
    unsigned char OutputAddBegin();

    unsigned char InputLens();
    unsigned char OutputLens();

    unsigned char ReadInPut(uint16_t add);
    unsigned char ReadOutPut(uint16_t add);
    bool WriteOutPut(uint16_t add,unsigned char data);
#ifdef USE_EPPROM
    bool initEPPROM();
    unsigned char readEPPROM(uint16_t add);
    bool writeEPPROM(uint16_t add,unsigned char data);
    void saveEPPROM();
    void write_rom_UChar(uint16_t add, unsigned char data);
    unsigned char read_rom_UChar(uint16_t add);

    void write_rom_Char(uint16_t add, char data);
    char read_rom_Char(uint16_t add);

    void write_rom_UInt(uint16_t add, unsigned int data);
    unsigned int read_rom_UInt(uint16_t add);

    void write_rom_Int(uint16_t add, int data);
    int read_rom_Int(uint16_t add);

    void write_rom_UInt32(uint16_t add, unsigned long data);
    unsigned long read_rom_UInt32(uint16_t add);

    void write_rom_Int32(uint16_t add, long data);
    long read_rom_Int32(uint16_t add);

    void write_rom_Float(uint16_t add, float data);
    float read_rom_Float(uint16_t add);

    void write_rom_Double(uint16_t add, double data);
    double read_rom_Double(uint16_t add);
    
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

    void write_rom_Block(uint16_t add, unsigned int lens,unsigned char *data);
    unsigned char read_rom_Block(uint16_t add, unsigned int lens,unsigned char *data);
    #ifdef USE_ExI2C
    bool initI2CEPPROM();
    unsigned char readI2C_rom(uint16_t add);
    bool writeI2C_rom(uint16_t add,unsigned char data);
    void write_I2C_rom_UChar(uint16_t add, unsigned char data);
    unsigned char read_I2C_rom_UChar(uint16_t add);

    void write_I2C_rom_Char(uint16_t add, char data);
    char read_I2C_rom_Char(uint16_t add);

    void write_I2C_rom_UInt(uint16_t add, unsigned int data);
    unsigned int read_I2C_rom_UInt(uint16_t add);

    void write_I2C_rom_Int(uint16_t add, int data);
    int read_I2C_rom_Int(uint16_t add);

    void write_I2C_rom_UInt32(uint16_t add, unsigned long data);
    unsigned long read_I2C_rom_UInt32(uint16_t add);

    void write_I2C_rom_Int32(uint16_t add, long data);
    long read_I2C_rom_Int32(uint16_t add);

    void write_I2C_rom_Float(uint16_t add, float data);
    float read_I2C_rom_Float(uint16_t add);

    void write_I2C_rom_Double(uint16_t add, double data);
    double read_I2C_rom_Double(uint16_t add);
    
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

    void write_I2C_rom_Block(uint16_t add, unsigned int lens,unsigned char *data);
    unsigned char read_I2C_rom_Block(uint16_t add, unsigned int lens,unsigned char *data);
    #endif
#endif
private:
protected:
};
