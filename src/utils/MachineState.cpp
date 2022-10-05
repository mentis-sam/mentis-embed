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

void MachineState::startState(uint8_t state, uint16_t* length) // FIXME:: LENGTH NEEDS TO BE A REFERENCE 
{
    if (state == none | length == NULL){

        Serial.printf("\nMachineState: Returning to none state \n\n");
        TempController::off();
        // LED
        ledcWrite(0, 0);
        _state.mode = none;
        _state.startT = 0;
        _state.endT   = 0;

        _saveState();
        return;
    }
    
    Serial.printf("\n /// Started State: %d, Length: %dHrs /// \n\n", state, *length);

    

    if (state == colonisation){
        TempController::setTemp(Settings::lerpSettings.c_temp);
        ledcWrite(0, 0);
    } else if (state == fruiting){
        TempController::setTemp(Settings::lerpSettings.f_temp);

        uint8_t duty = round(16 * static_cast<float>(Settings::lerpSettings.f_light)/11);

        ledcWrite(0, duty);
    } else if (state == dehydration){
        TempController::setTemp(Settings::lerpSettings.d_temp);
        digitalWrite(LED_PIN, LOW);
    }

    _state.mode = state;
    _state.startT = RTCModule::getTime().unixtime();

    // TODO: why cant I add the unixtime
    _state.endT   = _state.startT + *length*60*60;

    _saveState();
}

float MachineState::getStateProgress(void)
{
    uint32_t now = RTCModule::getTime().unixtime();
    if (_state.endT != _state.startT) {
        return  static_cast<float>(now - _state.startT) / static_cast<float>(_state.endT - _state.startT);
    } else {
        return 0;
    }
    
}

uint8_t MachineState::getState(void)
{
    return _state.mode;
}

void MachineState::_loadState(void)
{
    Settings::loadSettings();

    if (FileManager::exists("/state")){
        FileManager::read("/state", &_state, sizeof(_state));

        // TODO: this would be nicer as a switch
        if (_state.mode == none) {
            return;
        } else if (_state.mode == colonisation) {
            Nav::gotoScreen(&Nav::colonise_colonising);
            MachineState::startState(colonisation, &Settings::lerpSettings.c_timeperiod);
        } else if (_state.mode == fruiting){
            Nav::gotoScreen(&Nav::mycelium_fruiting);
            MachineState::startState(fruiting, &Settings::lerpSettings.f_timeperiod);
        } else if (_state.mode == dehydration) {
            // FIXME: This needs to be the new dehydration screen
            Nav::gotoScreen(&Nav::menu_dehydrate);
            MachineState::startState(dehydration, &Settings::lerpSettings.d_timeperiod);      
        }
    }
}

void MachineState::_saveState(void)
{
    FileManager::write("/state", &_state, sizeof(_state));
}

///

StateController::StateController(void)
{
}

// LOGIC FOR CHANGES OF STATE
void StateController::update(void)
{
    float progress = MachineState::getStateProgress();

    Serial.printf("StateController: %d, Progress: %f\n", MachineState::getState(), MachineState::getStateProgress());
    
    if (progress < 1) {return;}

    // STATE COMPLETE 

    uint8_t state = MachineState::getState();

    // TODO: notifications ??

    if (state == none) {
        return;
    } else if (state == colonisation) {
        Nav::gotoScreen(&Nav::mycelium_fruiting);
        MachineState::startState(fruiting, &Settings::lerpSettings.f_timeperiod);
    } else if (state == fruiting){
        Nav::gotoScreen(&Nav::menu_mycelium);
        MachineState::startState(none);
    } else if (state == dehydration) {
        Nav::gotoScreen(&Nav::menu_dehydrate);
        MachineState::startState(none);      
    }
}