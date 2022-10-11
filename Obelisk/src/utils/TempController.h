#ifndef TEMP_CONTROLLER
#define TEMP_CONTROLLER

#include "IO.h"

#include <TempModule.h>

class TempController{
public:
    TempController();

    static uint8_t initialise();

    static void setTemp(uint8_t temp, uint8_t speed);
    static void off();

    static void update(void);
private:
    static bool    _on;
    static uint8_t _temp;
    static bool    _heaterPin;
};

#endif /* TEMP_CONTROLLER */
