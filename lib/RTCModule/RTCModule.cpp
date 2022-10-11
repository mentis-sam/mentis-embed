#include "RTCModule.h"

RTC_DS1307 RTC;

RTCModule::RTCModule(void) 
{
}

uint8_t RTCModule::initialise(void)
{
    
    // TODO: Increase I2C clock speed currently at 100kHz
    //Wire.setClock(200000);   
    // Automatically uses pins 21, 22
    Wire.begin();
    //Serial.println(Wire.getClock());

    RTC.begin();

    // Check RTC address available TODO: Change this from a fixed var of 0x68
    byte error;
    Wire.beginTransmission(0x68);
    error = Wire.endTransmission();
    if (error == 0) {
        // TODO: Better error handling on this
        if (!RTC.isrunning()) {
        // following line sets the RTC to the date & time this sketch was compiled
        RTC.adjust(DateTime(__DATE__, __TIME__));
        }

        Serial.println("RTCModule: Initialised\n");
        return 0;
    }

    Serial.println("RTCModule: Failed to initialise\n");
    return 1;  
}

DateTime RTCModule::getTime(void)
{
    DateTime a = RTC.now();
    DateTime b = RTC.now();

    // TODO: Add recursion limit

    if (abs((int64_t)b.unixtime() - (int64_t)a.unixtime()) < 5 ){
        return b;
    }else{
        Serial.println("RTCModule: Erronious time returned .. trying again");
        return RTCModule::getTime();
    }
}

