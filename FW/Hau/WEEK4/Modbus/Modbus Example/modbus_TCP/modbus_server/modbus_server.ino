//nhuoc diem khi client connect toi server(master -> slave) -> server vao vong loop -> client phai disconnect thi server moi chay tiep 
#include <WiFi.h>
#include <ModbusTCPSlave.h> 


//WIFI Settings
//byte ip[]      = { 192, 168, 1, 126};
//byte gateway[] = { 192, 168, 1, 1 };
//byte subnet[]  = { 255, 255, 255, 0 };
ModbusTCPSlave Mb;

void valor() {

      
      Mb.MBHoldingRegister[0] = random(0,51); //random value for holdRes adr 0

     Serial.print("MBHoldingRegister[0]");
     Serial.println(Mb.MBHoldingRegister[0]);
     Serial.print("MBHoldingRegister[1]");
     Serial.println(Mb.MBHoldingRegister[1]);

  }

void setup()
{

    Serial.begin(115200);  
    Mb.begin("SSID", "password");
//  Mb.begin("SSID", "PASSWORD", ip, gateway, subnet);
  delay(100);
}
unsigned long count = 0;
void loop()
{
  Mb.Run(); 
  delay(10);
  if(millis() - count > 500)
  {
    valor();
    count = millis();
  }
}
