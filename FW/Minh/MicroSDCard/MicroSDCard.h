#ifndef _MicroSDCard_H
#define _MicroSDCard_H

#include "Arduino.h"
#include "SD.h"
#include "FS.h"
#include "SPI.h"

class MicroSDCard{
    private: 
        void _listDir(fs::FS &fs, const char * dirname, uint8_t levels);
        void _createDir(fs::FS &fs, const char * path);
        void _removeDir(fs::FS &fs, const char * path);
        void _readFile(fs::FS &fs, const char * path);
        void _writeFile(fs::FS &fs, const char * path, const char * message);
        void _appendFile(fs::FS &fs, const char * path, const char * message);
        void _renameFile(fs::FS &fs, const char * path1, const char * path2);
        void _deleteFile(fs::FS &fs, const char * path);
    public: 
        void listDir(const char * dirname, uint8_t levels);
        void listDir(const char * dirname);
        void createDir(const char * path);
        void removeDir(const char * path);
        void readFile(const char * path);
        void writeFile(const char * path, const char * message);
        void appendFile(const char * path, const char * message);
        void renameFile(const char * path1, const char * path2);
        void deleteFile(const char * path);
        uint64_t SDSize();
        boolean SDbegin();
};
extern MicroSDCard SDCard;
#endif//