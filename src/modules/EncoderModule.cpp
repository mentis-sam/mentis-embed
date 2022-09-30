#include "EncoderModule.h"

portMUX_TYPE gpioMux = portMUX_INITIALIZER_UNLOCKED;

volatile bool EncoderModule::_selectFlag = 0;

volatile int8_t EncoderModule::_rotValue;

int8_t state = 0;
int8_t result = 0;

const uint8_t ttable[7][4] = {
  {0, 2, 4, 0},
  {3, 0, 1, 0 | 16},
  {3, 2, 0, 0},
  {3, 2, 1, 0},
  {6, 0, 4, 0},
  {6, 5, 0, 0 | 32},
  {6, 5, 4, 0},
};

EncoderModule::EncoderModule(void)
{
}

int8_t EncoderModule::initialise()
{
    // TODO: Add debugging
    pinMode(ENCODER_PINA, INPUT_PULLUP);
    pinMode(ENCODER_PINB, INPUT_PULLUP);
    pinMode(ENCODER_PINS, INPUT_PULLUP);

    attachInterrupt(ENCODER_PINA, _rotaryEncorderISR, CHANGE);
    attachInterrupt(ENCODER_PINB, _rotaryEncorderISR, CHANGE);
    attachInterrupt(ENCODER_PINS, _rotarySwitchISR,   RISING);

    Serial.println("Encoder module initialised\n");

    return 0;
}

void EncoderModule::_rotaryEncorderISR()
{
    // TODO: Optimise this code

    // Refer to https://github.com/buxtronix/arduino/tree/master/libraries/Rotary

    // Grab state of input pins.
	// Determine new state from the pins and state table.
	state = ttable[state & 0xf][(digitalRead(ENCODER_PINB) << 1) | digitalRead(ENCODER_PINA)];
	result = state & 48;

	//portENTER_CRITICAL_ISR(&gpioMux);
	// Right rotation.
	if(result == 16){
		_rotValue++;
	}
	// Left rotation.
	else if(result == 32){
		_rotValue--;
	}
	//portEXIT_CRITICAL_ISR(&gpioMux);
}

void EncoderModule::_rotarySwitchISR()
{
    static long lastSwitchTrigger = 0;
	long t = millis();

	if (t - lastSwitchTrigger < 250)
		return;
	lastSwitchTrigger = t;

    portENTER_CRITICAL_ISR(&gpioMux);
    _selectFlag = 1;
    portEXIT_CRITICAL_ISR(&gpioMux);
}

bool EncoderModule::_checkFlagRS(volatile bool& flag)
{
    // Reset flag on lookup
    if (flag){
        flag = 0;
        return 1;
    }
    return 0;
}

bool EncoderModule::leftFlag(void)
{
    if (_rotValue < 0) {
        _rotValue++;
        return 1;
    }
    return 0;
}

bool EncoderModule::rightFlag(void)
{
    if (_rotValue > 0) {
        _rotValue--;
        return 1;
    }
    return 0;
}

bool EncoderModule::selectFlag(void)
{
    // Reset flag on lookup
    if (_selectFlag){
        _selectFlag = 0;
        return 1;
    }
    return 0;
}

int8_t EncoderModule::getRotation(void){ return _rotValue; }
