#ifndef ENCODER_MODULE
#define ENCODER_MODULE

#include <Arduino.h>
#include <stdint.h>

#define ENCODER_PINA 26
#define ENCODER_PINB 27
#define ENCODER_PINS 25

class EncoderModule {
public:
    EncoderModule(void);
    static int8_t initialise();

    static bool leftFlag(void);
    static bool rightFlag(void);
    static bool selectFlag(void);

    static int8_t getRotation(void);
private:
    static void IRAM_ATTR _rotaryEncorderISR(void);
    static void IRAM_ATTR _rotarySwitchISR(void);

    static bool _checkFlagRS(volatile bool& flag);

    static volatile bool _selectFlag;

    static volatile int8_t _rotValue;
};


#endif /* ENCODER_MODULE */