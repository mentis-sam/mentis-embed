#include "IO.h"

namespace IO {

uint8_t initialise(void){
    // FAN
    pinMode(FAN_PIN, OUTPUT);

    // HEATER
    pinMode(HEATER_PIN, OUTPUT);

    // LED
    pinMode(LED_PIN, OUTPUT);
    return 0;
}

}
