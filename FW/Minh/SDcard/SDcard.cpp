#include "Arduino.h"
#include "SD_Card.h"

void SDcard::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void SDcard::createDir(fs::FS &fs, const char * path){
    if(fs.mkdir(path)){
        return 1; //Hoan thanh
    } else {
        return 0;
    }
}

void SDcard::removeDir(fs::FS &fs, const char * path){
    if(fs.rmdir(path)){
        return 1; //Hoan thanh
    } else {
        return 0;
    }
}

void SDcard::readFile(fs::FS &fs, const char * path){
    File file = fs.open(path);
    if(!file){
        return;
    }
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void SDcard::writeFile(fs::FS &fs, const char * path, const char * message){
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        return 0; //Failed
    }
    file.close();
}

void SDcard::appendFile(fs::FS &fs, const char * path, const char * message){
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        return 0;
    }
    file.close();
}

void SDcard::renameFile(fs::FS &fs, const char * path1, const char * path2){
    if (fs.rename(path1, path2)) {
        return 1;
    } else {
        return 0; //Failed
    }
}

void SDcard::deleteFile(fs::FS &fs, const char * path){
    if(fs.remove(path)){
       return 1;
    } else {
        return 0; //Failed
    }
}

SDcard:SDcard()
{
}

SDcard::~SDcard()
{
}
SDcard Card;