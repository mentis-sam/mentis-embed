#include "IO.h"

namespace IO {

uint8_t initialise(void){
    // FAN
    pinMode(FAN_PIN, OUTPUT);
    // HEATER
    pinMode(HEATER_PIN, OUTPUT);
    // LED
    pinMode(LED_PIN, OUTPUT);

    // LED
    pinMode(BUZZER_PIN, OUTPUT);

    

    ledcAttachPin(LED_PIN, 0);
    // 1000Hz & 16 bit of resolution
    ledcSetup(0, 1000, 4);

    ledcAttachPin(BUZZER_PIN, 1);
    ledcSetup(1, 5000, 4);

    //ledcAttachPin(FAN_PIN, 2);
    //ledcSetup(2, 1000, 4);

    Serial.println("IO: Initialised");
    return 0;
}

}

