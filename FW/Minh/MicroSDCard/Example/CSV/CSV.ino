#include <MicroSDCard.h>
void setup() {
  Serial.begin(115200);
    if(!SDCard.SDbegin(5)){
        Serial.println("Card Mount Failed");
        return;
    }
   SDCard.writeColumnCSV("/data.csv", "ID, Name, Class");
}
void loop() {
  String s = String(random(10)) + String(random(10)) + String(random(10));
  SDCard.writeRowCSV("/data.csv", s.c_str());
}
