#include "Arduino.h"
#define USE_EPPROM

#define R8BIT 256
#define R16BIT 256
#define R32BIT 256    // float memory
#define RFLOAT 256    // float memory
#define RLONG 256     // long memory
#define ADD_LENS R8BIT
#ifdef USE_EPPROM
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
static unsigned char _maxOut =1;
static unsigned char _maxIn =1;
static unsigned char _OutputStart =1;
static unsigned char _InputStart =0;

static unsigned char DevUChar[R8BIT];
static char DevChar[R8BIT];

static unsigned int DevUInt[R16BIT];
static int DevInt[R16BIT];

static unsigned long DevUInt32[R32BIT];
static long DevInt32[R32BIT];

static float DevFloat[RFLOAT];
static double DevDouble[RFLOAT];

class DevMemory
{
public:
    static void write_ram_UChar(unsigned char add, unsigned char data);
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
    static void write_rom_UChar(unsigned char add, unsigned char data);
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
#endif
private:
protected:
    static long offset;
};
