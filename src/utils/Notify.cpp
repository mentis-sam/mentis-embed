#include "Notify.h"


bool Notify::sleep  = false;

bool Notify::_notify = false;
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
    if (_notify && sleep) {
        if(millis() > _screenTime + 3000){
            _screenOn = !_screenOn;
        }

        if(_screenOn){
            digitalWrite(BL_PIN, HIGH);
        }else{
            digitalWrite(BL_PIN, LOW);
        }
    }

    if (_notify == false && sleep){
        digitalWrite(BL_PIN, LOW);
    }

    if (_notify == false && sleep == false){
        digitalWrite(BL_PIN, HIGH);
    }
}

void Notify::clear_notification(){
    digitalWrite(BL_PIN, HIGH);
    _notify = false;
}