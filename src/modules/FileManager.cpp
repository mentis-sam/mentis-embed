#include "FileManager.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

uint8_t FileManager::initialise()
{
    if(!SPIFFS.begin(true)){
        Serial.println("FileManager: SPIFFS Mount Failed");
        return 1;
    }

    return 0;
}

bool FileManager::exists(const char* file)
{
    return SPIFFS.exists(file);
}

void FileManager::read(const char* file, void *obj, uint8_t size)
{
    Serial.printf("FileManager: Reading file ");
    Serial.println(file);
    File myFile = SPIFFS.open(file, FILE_READ);

    if (!myFile) {
        Serial.println("FileManager: There was an error opening the file for reading");
        return;
    }
    
    myFile.readBytes((char*)obj, sizeof(obj));
    myFile.close();
}

void FileManager::write(const char* file, void *obj, uint8_t size)
{
    Serial.printf("FileManager: Writing file ");
    Serial.println(file);
    File myFile = SPIFFS.open(file, FILE_WRITE);

    if (!myFile) {
        Serial.println("FileManager: There was an error opening the file for writing");
        return;
    }

    myFile.write((byte*)obj, sizeof(obj));
    myFile.close();
}
