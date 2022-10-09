#include "Notify.h"


bool Notify::sleep  = false;

bool Notify::_notify = false;

bool Notify::_lastNotify = false;
bool Notify::_lastSleep = false;
bool Notify::_screenOn = true;
int Notify::_screenTime = 0;

Notify::Notify()
{
}

void Notify::set_notification(){
    _notify = true;
}

void Notify::update(){
    // Flash screen

    //FIXME: only needs to update on state change
    if (_lastNotify == _notify && _lastSleep == sleep){return;}

    if (_notify){
        if (sleep){
            if(millis() > _screenTime + 2000){
            _screenOn = !_screenOn;
            }
            if(_screenOn){
                digitalWrite(BL_PIN, HIGH);
            }else{
                digitalWrite(BL_PIN, LOW);
            }
        }else{
            digitalWrite(BL_PIN, HIGH);
        }
        

    }
    
    if (_notify == false){
        if (sleep) {
            digitalWrite(BL_PIN, LOW);
        }else {
            digitalWrite(BL_PIN, HIGH);
        }
    }

    _lastNotify = _notify;
    _lastSleep = sleep;
    
}

void Notify::clear_notification(){
    digitalWrite(BL_PIN, HIGH);
    _notify = false;
}