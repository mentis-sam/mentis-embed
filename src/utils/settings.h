#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include "modules/FileManager.h"

enum beep_settings {on_harvest, on_drying, both};

struct Settings{
    uint8_t c_timeperiod;
    uint8_t c_temp;
    uint8_t c_airflow;

    uint8_t f_timeperiod;
    uint8_t f_temp;
    uint8_t f_airflow;
    uint8_t f_light;

    uint8_t d_timeperiod;
    uint8_t d_temp;
    uint8_t d_airflow;

    uint8_t beep;
};

extern Settings settings;

void loadSettings(void);
void saveSettings(void);

#endif /* SETTINGS */