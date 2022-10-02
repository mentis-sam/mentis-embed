#include "MachineState.h"

uint8_t  MachineState::_state = none;
uint32_t MachineState::_stateStart = 0;
uint32_t MachineState::_stateEnd = 0;

MachineState::MachineState(void)
{
}

uint8_t MachineState::initialise(void)
{
    _loadState();
    return 0;
}

void MachineState::startState(uint8_t state, DateTime length)
{
    
    Serial.printf("Started State: %d, Length: %dD, %dH", state, length.day(), length.hour());

    if (state == none){
        TempController::off();
        // LED
        ledcWrite(0, 0);
    } else if (state == colonisation){
        TempController::setTemp(c_temp);
        ledcWrite(0, 0);
    } else if (state == fruiting){
        TempController::setTemp(f_temp);

        uint8_t duty = round(16 * (float)f_light/11);

        ledcWrite(0, duty);
    } else if (state == dehydration){
        TempController::setTemp(d_temp);
        digitalWrite(LED_PIN, LOW);
    }

    _state = state;
    _stateStart = RTCModule::getTime().unixtime();
    _stateEnd   = _stateStart + length.unixtime();
    _saveState();
}

float MachineState::getStateProgress(void)
{
    uint32_t now = RTCModule::getTime().unixtime();
    return (float)(_stateEnd - now) / (_stateEnd - _stateStart);
}

uint8_t MachineState::getState(void)
{
    return _state;
}

void MachineState::_loadState(void)
{
}

void MachineState::_saveState(void)
{
}

///

StateController::StateController(void)
{
}


// LOGIC FOR CHANGES OF STATE
void StateController::update(void)
{
    float progress = MachineState::getStateProgress();

    Serial.printf("State: %d, Progress: %fH", MachineState::getState(), MachineState::getStateProgress());
    
    if (progress < 1) {return;}

    // STATE COMPLETE 

    uint8_t state = MachineState::getState();

    // TODO: notifications ??

    if (state == none) {
        return;
    } else if (state == colonisation) {
        Nav::gotoScreen(&Nav::mycelium_fruiting);
        MachineState::startState(fruiting, DateTime(0, 0, f_timeperiod, 0, 0, 0));
    } else if (state == fruiting){
        Nav::gotoScreen(&Nav::menu_mycelium);
        MachineState::startState(none, DateTime(0, 0, 0, 0, 0, 0));
    } else if (state == dehydration) {
        Nav::gotoScreen(&Nav::menu_dehydrate);
        MachineState::startState(none, DateTime(0, 0, 0, 0, 0, 0));      
    }
}