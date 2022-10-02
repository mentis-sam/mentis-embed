#include "MachineState.h"

State_Settings MachineState::_state = {
    .mode = none,
    .startT = 0,
    .endT = 0
};

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
    
    Serial.printf("\n /// Started State: %d, Length: %dD, %dH /// \n\n", state, length.day(), length.hour());

    if (state == none){
        TempController::off();
        // LED
        ledcWrite(0, 0);
    } else if (state == colonisation){
        TempController::setTemp(settings.c_temp);
        ledcWrite(0, 0);
    } else if (state == fruiting){
        TempController::setTemp(settings.f_temp);

        uint8_t duty = round(16 * static_cast<float>(settings.f_light)/11);

        ledcWrite(0, duty);
    } else if (state == dehydration){
        TempController::setTemp(settings.d_temp);
        digitalWrite(LED_PIN, LOW);
    }

    _state.mode = state;
    _state.startT = RTCModule::getTime().unixtime();

    // TODO: why cant I add the unixtime
    _state.endT   = _state.startT + length.day()*24*60*60 + length.hour()*60*60;

    Serial.printf("Start: %d, End: %d\n", _state.endT, _state.endT);

    _saveState();
}

float MachineState::getStateProgress(void)
{
    uint32_t now = RTCModule::getTime().unixtime();
    return  static_cast<float>(now - _state.startT) / static_cast<float>(_state.endT - _state.startT);
}

uint8_t MachineState::getState(void)
{
    return _state.mode;
}

void MachineState::_loadState(void)
{
    loadSettings();
    // Load state
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

    Serial.printf("State: %d, Progress: %f\n", MachineState::getState(), MachineState::getStateProgress());
    
    if (progress < 1) {return;}

    // STATE COMPLETE 

    uint8_t state = MachineState::getState();

    // TODO: notifications ??

    if (state == none) {
        return;
    } else if (state == colonisation) {
        Nav::gotoScreen(&Nav::mycelium_fruiting);
        MachineState::startState(fruiting, DateTime(0, 0, settings.f_timeperiod, 0, 0, 0));
    } else if (state == fruiting){
        Nav::gotoScreen(&Nav::menu_mycelium);
        MachineState::startState(none, DateTime(0, 0, 0, 0, 0, 0));
    } else if (state == dehydration) {
        Nav::gotoScreen(&Nav::menu_dehydrate);
        MachineState::startState(none, DateTime(0, 0, 0, 0, 0, 0));      
    }
}