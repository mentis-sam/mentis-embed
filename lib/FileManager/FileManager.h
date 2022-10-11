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

    static uint8_t initialise(void);
    static bool exists(const char* file);

    static void read(const char* file, void *obj, uint8_t size);
    static void write(const char* file, void *obj, uint8_t size);
private:

};

#endif