#include "IO.h"

namespace IO {

uint8_t initialise(void){
    // FAN
    pinMode(FAN_PIN, OUTPUT);
    // HEATER
    pinMode(HEATER_PIN, OUTPUT);
    // LED
    pinMode(LED_PIN, OUTPUT);

    ledcAttachPin(LED_PIN, 0);
    // 1000Hz & 16 bit of resolution
    ledcSetup(0, 1000, 4);
    
    return 0;
}

}

