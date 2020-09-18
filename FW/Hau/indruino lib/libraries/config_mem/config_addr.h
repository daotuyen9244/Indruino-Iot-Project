#ifndef _CONFIG_ADDR_H
#define _CONFIG_ADDR_H
#include "config_mem.h"

#ifdef ESP32 ||ESP8266
#include "esp32_addr.h"
#else
#include "mega_addr.h"
#endif


#endif //_CONFIG_ADDR_H
