#include <MicroSDCard.h>

void setup(){
  Serial.begin(115200);
    if(!SDCard.SDbegin()){
        Serial.println("Card Mount Failed");
        return;
    }
    SDCard.listDir("/");
    //SDCard.listDir("/");
    //SDCard.writeFile("/Xinchao.txt", "Hello ");
    //SDCard.appendFile("/hello.txt", "World!\n");
    //SDCard.readFile("/hello.txt");
    //SDCard.deleteFile("/foo.txt");
    //SDCard.renameFile("/hello.txt", "/foo.txt");
    //SDCard.readFile("/foo.txt");
}
void loop(){
  
}
