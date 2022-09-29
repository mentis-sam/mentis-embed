#ifndef TEMP_MODULE
#define TEMP_MODULE

#include <DS18B20.h>

#define TEMP_PIN 32

class TempModule {
public:
    TempModule(void);
    static uint8_t initialise();
    static float    getTempC(void);
private:
    static DS18B20   _ds;
};


#endif /* TEMP_MODULE */
