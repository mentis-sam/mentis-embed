#ifndef TEMP_MODULE
#define TEMP_MODULE

#include <DS18B20.h>

class TempModule {
public:
    TempModule(void);
    static int   initialise(uint8_t pin);
    static float getTempC(void);
private:
    static DS18B20   _ds;
};


#endif /* TEMP_MODULE */
