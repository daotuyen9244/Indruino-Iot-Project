#include "Arduino.h"
#include "MicroSDCard.h"

void MicroSDCard::_listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

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
                MicroSDCard::_listDir(fs, file.name(), levels -1);
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
void MicroSDCard::listDir(const char * dirname, uint8_t levels)
        {
            return _listDir(SD, dirname, levels);
        }
void MicroSDCard::listDir(const char * dirname)
        {
            return _listDir(SD, dirname, 0);
        }
void MicroSDCard::_createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}
void MicroSDCard::createDir(const char * path)
        {
            return _createDir(SD, path);
        }
void MicroSDCard::_removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}
void MicroSDCard::removeDir(const char * path)
        {
            return _removeDir(SD, path);
        }
void MicroSDCard::_readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
void MicroSDCard::readFile(const char * path)
        {
            return _readFile(SD, path);
        }
void MicroSDCard::_writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}
void MicroSDCard::writeFile(const char * path, const char * message)
        {
            return _writeFile(SD, path, message);
        }
void MicroSDCard::_appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}
void MicroSDCard::appendFile(const char * path, const char * message)
        {
            return _appendFile(SD, path, message);
        }
void MicroSDCard::_renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}
void MicroSDCard::renameFile(const char * path1, const char * path2)
        {
            return _renameFile(SD, path1, path2);
        }
void MicroSDCard::_deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}
void MicroSDCard::deleteFile(const char * path)
        {
            return _deleteFile(SD, path);
        }
void MicroSDCard::_writeColumnCSV(fs::FS &fs, const char * path, const char * columnname){
    _writeFile(fs, path, columnname);
}
void MicroSDCard::writeColumnCSV(const char * path, const char * columnname){
   String data = String(columnname) + "\r\n";
   return _writeColumnCSV(SD, path, data.c_str());
}
void MicroSDCard::_writeRowCSV(fs::FS &fs, const char * path, const char * row){
    _appendFile(SD, path, row);
}
void MicroSDCard::writeRowCSV(const char * path, const char * row){
   String data = String(row) + "\r\n";
   return _writeRowCSV(SD, path, data.c_str());
}
uint64_t MicroSDCard::SDSize(){
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    return cardSize;
}

boolean MicroSDCard::SDbegin(){
    return SD.begin();
}
MicroSDCard SDCard;