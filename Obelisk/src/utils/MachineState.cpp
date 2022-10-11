#include "MachineState.h"

State_Settings MachineState::_state = {
    .mode = none,
    .startT = 0,
    .endT = 0
};

float MachineState::_timeLeft = 0;

MachineState::MachineState(void)
{
}

uint8_t MachineState::initialise(void)
{
    _loadState();
    return 0;
}

// TODO: quite hacky
void MachineState::startState(uint8_t state, uint16_t* length, bool save) // FIXME:: LENGTH NEEDS TO BE A REFERENCE 
{
    if (state == none | length == NULL){

        Serial.printf("\nMachineState: Returning to none state \n\n");
        TempController::off();
        // LED
        ledcWrite(0, 0);
        

        if (save) {
            _state.mode = none;
            _state.startT = 0;
            _state.endT   = 0;
            _saveState();
        }
        return;
    }
    
    Serial.printf("\n /// Started State: %d, Length: %dHrs /// \n\n", state, *length);

    if (state == colonisation){
        TempController::setTemp(Settings::lerpSettings.c_temp, Settings::lerpSettings.c_airflow);
        ledcWrite(0, 0);
    } else if (state == fruiting){
        TempController::setTemp(Settings::lerpSettings.f_temp, Settings::lerpSettings.f_airflow);

        //uint8_t duty = round(Settings::lerpSettings.f_light);
        ledcWrite(0, Settings::lerpSettings.f_light);
    } else if (state == dehydration){
        TempController::setTemp(Settings::lerpSettings.d_temp, 15);
        digitalWrite(LED_PIN, LOW);
    }

    if (save) {
        _state.mode = state;
        _state.startT = RTCModule::getTime().unixtime();

        // TODO: why cant I add the unixtime
        _state.endT   = _state.startT + *length*60*60;

        _saveState();
    }

    updateStateProgress();
}

float MachineState::updateStateProgress(void)
{
    uint32_t now = RTCModule::getTime().unixtime();

    // this casts to float with no check FIXME:
    _timeLeft = _state.endT - now;

    if (_state.endT != _state.startT) {
        float f = static_cast<float>(now - _state.startT) / static_cast<float>(_state.endT - _state.startT);

        if (f < 1){
            return f;
        }else{
            return 1;
        }
    } else {
        return 0;
    }
}

uint8_t MachineState::getState(void)
{
    return _state.mode;
}

// Returns time left in hrs
uint32_t MachineState::getTimeLeft(void)
{
     return std::ceil(_timeLeft / (60*60));
}

void MachineState::_loadState(void)
{
    Settings::loadSettings();

    if (FileManager::exists("/state")){
        FileManager::read("/state", &_state, sizeof(_state));

        // TODO: this would be nicer as a switch
        if (_state.mode == none) {
            Nav::gotoScreen(&Nav::menu_colonise);
            MachineState::startState(none, NULL, false);
        } else if (_state.mode == colonisation) {
            Nav::gotoScreen(&Nav::colonise_colonising);
            MachineState::startState(colonisation, &Settings::lerpSettings.c_timeperiod, false);
        } else if (_state.mode == fruiting){
            Nav::gotoScreen(&Nav::mycelium_fruiting);
            MachineState::startState(fruiting, &Settings::lerpSettings.f_timeperiod, false);
        } else if (_state.mode == dehydration) {
            Nav::gotoScreen(&Nav::dehydrate_dehydrating);
            MachineState::startState(dehydration, &Settings::lerpSettings.d_timeperiod, false);      
        }    
    }else{
        _saveState();
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
    float progress = MachineState::updateStateProgress();

    Serial.printf("StateController: %d, Progress: %f\n", MachineState::getState(), MachineState::updateStateProgress());
    
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
        // Do notification
        Notify::set_notification();
    } else if (state == dehydration) {
        Nav::gotoScreen(&Nav::dehydrate_complete);
        MachineState::startState(none);     
        Notify::set_notification(); 
    }
}