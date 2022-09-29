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
            Serial.printf("Setting Temperature Module to low res mode\n");
            _ds.setResolution(9);
        }

        Serial.println("Temperature module initialised\n");
        return 0;
    } 

    Serial.println("Temperature module failed to initialise\n");
    return 1;
}

float TempModule::getTempC(void)
{
    if (selected) {
        return _ds.getTempC();
    }else{
        return -273.0; // TempModule didn't init correctly return nonsense val
    }
}