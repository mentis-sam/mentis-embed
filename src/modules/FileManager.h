#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#pragma once

#include <stdint.h>
#include <FS.h>
#include <SPIFFS.h>

class FileManager
{
public:
    FileManager();
    ~FileManager();

    bool exists(const char* file);

    void read(const char* file, void *obj, uint8_t size);
    void write(const char* file, void *obj, uint8_t size);
private:

};

#endif