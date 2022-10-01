#ifndef TEMP_CONTROLLER
#define TEMP_CONTROLLER

#include "IO.h"
#include "modules/TempModule.h"

class TempController{
public:
    TempController();

    static void initialise();

    static void setTemp(uint8_t temp);
    static void off();

    static void update(void);
private:
    static bool    _on;
    static uint8_t _temp;
    static bool    _heaterPin;
};

#endif /* TEMP_CONTROLLER */
