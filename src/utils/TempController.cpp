#include "TempController.h"

const float hyst = 1; 

bool    TempController::_on = false;
uint8_t TempController::_temp = 0;
bool    TempController::_heaterPin = false;

TempController::TempController()
{}

uint8_t TempController::initialise()
{
    TempController::off();
    return 0;
}

void TempController::setTemp(uint8_t temp)
{
    digitalWrite(FAN_PIN, HIGH);
    _on = true;
    _temp = temp;
}

void TempController::off()
{
    digitalWrite(FAN_PIN, LOW); digitalWrite(HEATER_PIN, LOW);
    _on = false;
}

void TempController::update(void)
{
    // OFF
    if (!_on) { return; }

    float temp = TempModule::getTempC();

    // TODO: ADD PID CONTROLLER NOT JUST HYST
    if (_heaterPin & (temp > _temp + (hyst / 2))){
        digitalWrite(HEATER_PIN, LOW);
        _heaterPin = false;
    }

    if (!_heaterPin & (temp < _temp - (hyst / 2))) {
        digitalWrite(HEATER_PIN, HIGH);
        _heaterPin = true;
    }
}

