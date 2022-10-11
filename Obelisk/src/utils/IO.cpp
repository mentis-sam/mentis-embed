#include "IO.h"

namespace IO {

uint8_t initialise(void){

    pinMode(FAN_PIN, OUTPUT);

    pinMode(HEATER_PIN, OUTPUT);

    pinMode(LED_PIN, OUTPUT);

    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(BL_PIN, OUTPUT);
    

    
    // 1000Hz & 16 bit of resolution
    //TODO: label these PWM channels
    ledcAttachPin(LED_PIN, 0);
    ledcSetup(0, 1000, 4);

    ledcAttachPin(BUZZER_PIN, 1);
    ledcSetup(1, 5000, 4);

    Serial.println("IO: Initialised");
    return 0;
}

}

