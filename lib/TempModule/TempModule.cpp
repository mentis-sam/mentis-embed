#include "TempModule.h"

uint8_t selected;

DS18B20 TempModule::_ds(0);

TempModule::TempModule(void) 
{
}

uint8_t TempModule::initialise()
{
    _ds = DS18B20(TEMP_PIN);

    selected = _ds.selectNext();

    if (selected) {
        
        // Check tempModule in low resolution mode, if not set mode
        if (_ds.getResolution() != 9){
            Serial.printf("TempModule: Setting low res mode\n");
            _ds.setResolution(9);
        }

        Serial.println("TempModule: Initialised\n");
        return 0;
    } 

    Serial.println("TempModule: Failed to initialise\n");
    return 1;
}

float TempModule::getTempC(void)
{
    if (selected) {
        return _ds.getTempC();
    }else{
        // Return high value so that it doesnt turn heater on
        return 1000; // TempModule didn't init correctly return nonsense val
    }
}