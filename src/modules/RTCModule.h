#ifndef RTC_MODULE
#define RTC_MODULE

#include <Arduino.h>
#include <Wire.h>

#include "RTClib.h"

class RTCModule {
public:
    RTCModule(void);
    static uint8_t  initialise(void);
    static DateTime getTime(void);
private:

};


#endif /* RTC_MODULE */
