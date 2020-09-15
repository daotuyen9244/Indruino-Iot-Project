#include "indruino_data.h"

Indruino indruino;

void setup()
{
    indruino.init();
    //this command will create default ram and init ram with size max of ram. And init Rom.
    //default ram at pos 0
    Serial.begin(115200);
    while (!Serial); //Serial debug
    indruino.createNewRam(10, 1); //create new Ram at pos 1 with size = 10 byte
    
    
}
void loop()
{
}
