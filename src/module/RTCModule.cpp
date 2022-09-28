#include "RTCModule.h"

RTC_DS1307 RTC;

RTCModule::RTCModule(void) 
{
}

int RTCModule::initialise(void)
{
    
    // TODO: Increase I2C clock speed currently at 100kHz
    //Wire.setClock(200000);   
    Wire.begin();
    Serial.println(Wire.getClock());

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

        Serial.println("RTC module initialised\n");
        return 0;
    }

    Serial.println("RTC module failed to initialise\n");
    return 1;  
}

DateTime RTCModule::getTime(void)
{
    return RTC.now();
}

   // Search for RTC address if not already known

    /*
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for(address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
        Serial.print("I2C device found at address 0x");
        if (address<16) {
            Serial.print("0");
        }
        Serial.println(address,HEX);
        nDevices++;
        }
        else if (error==4) {
        Serial.print("Unknow error at address 0x");
        if (address<16) {
            Serial.print("0");
        }
        Serial.println(address,HEX);
        }    
    }
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    }
    else {
        Serial.println("done\n");
    }*/