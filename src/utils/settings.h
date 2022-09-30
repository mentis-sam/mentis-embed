#ifndef SETTINGS
#define SETTINGS

#include <stdint.h>

enum beep_settings {on_harvest, on_drying, both};

extern uint8_t c_timeperiod;
extern uint8_t c_temp;
extern uint8_t c_airflow;

extern uint8_t f_timeperiod; 
extern uint8_t f_temp;
extern uint8_t f_airflow;
extern uint8_t f_light;

extern uint8_t beep;

#endif /* SETTINGS */