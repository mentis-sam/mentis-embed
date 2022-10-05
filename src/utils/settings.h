#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdint.h>
#include "modules/FileManager.h"

enum beep_settings {on_harvest, on_drying, both};
enum Mode          { none, colonisation , fruiting , dehydration };

struct Settings_S{
    uint16_t c_timeperiod;
    uint16_t c_temp;
    uint16_t c_airflow;

    uint16_t f_timeperiod;
    uint16_t f_temp;
    uint16_t f_airflow;
    uint16_t f_light;

    uint16_t d_timeperiod;
    uint16_t d_temp;

    uint16_t beep;
};

struct Lerp {
    uint16_t s_range;
    uint16_t l_min;
    uint16_t l_max;
};

struct Settings_Lerp{
    Lerp c_timeperiod;
    Lerp c_temp;
    Lerp c_airflow;

    Lerp f_timeperiod;
    Lerp f_temp;
    Lerp f_airflow;
    Lerp f_light;

    Lerp d_timeperiod;
    Lerp d_temp;
    Lerp d_airflow;
};

class Settings{
public:
    Settings();

    static void loadSettings(void);
    static void saveSettings(void);
    static void factory_reset(void);

    static Settings_S settings;
    static Settings_S lerpSettings;
private:
    const static Settings_S _f_settings;
    const static Settings_Lerp _settingsLerp;
    static void calcLerpSettings();
    static void _lerp(uint16_t & setting, Lerp lerp);
};


#endif /* SETTINGS */