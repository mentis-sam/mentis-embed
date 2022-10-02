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
    Serial.println("FileManager: Reading file");
    File myFile = SPIFFS.open(file, FILE_WRITE);

    if (!myFile) {
        Serial.println("FileManager: There was an error opening the file for reading");
        return;
    }
    
    myFile.read((byte *)&obj, sizeof(obj));
    myFile.close();
}

void FileManager::write(const char* file, void *obj, uint8_t size)
{
    Serial.println("FileManager: Writing file");
    File myFile = SPIFFS.open(file, FILE_WRITE);

    if (!myFile) {
        Serial.println("FileManager: There was an error opening the file for writing");
        return;
    }

    myFile.write((uint8_t *)&obj, sizeof(obj));
    myFile.close();
}
