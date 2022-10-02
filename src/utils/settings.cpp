#include "settings.h"


// FIXME: Works but should probs refactor this whole thing
Settings_S Settings::settings = {
    .c_timeperiod = 21,
    .c_temp = 5,
    .c_airflow = 5,

    .f_timeperiod = 14,
    .f_temp = 5,
    .f_airflow = 5,
    .f_light = 5,

    .d_timeperiod = 14,
    .d_temp = 50,
    .d_airflow = 5,

    .beep = 0
};

Settings_S Settings::lerpSettings = Settings::settings;

const Settings_Lerp Settings::_settingsLerp = {
    .c_timeperiod = { .s_range = 50, .l_min = 6, .l_max = 50},
    .c_temp = { .s_range = 50, .l_min = 6, .l_max = 50},
    .c_airflow = { .s_range = 50, .l_min = 6, .l_max = 50},

    .f_timeperiod = {.s_range = 50, .l_min = 6, .l_max = 50},
    .f_temp = { .s_range = 50, .l_min = 6, .l_max = 50},
    .f_airflow = { .s_range = 50, .l_min = 0, .l_max = 10},
    .f_light = { .s_range = 50, .l_min = 0, .l_max = 10},

    .d_timeperiod = { .s_range = 50, .l_min = 0, .l_max = 10},
    .d_temp = { .s_range = 50, .l_min = 0, .l_max = 10},
    .d_airflow { .s_range = 50, .l_min = 0, .l_max = 10},
};

void Settings::calcLerpSettings(){
    lerpSettings = settings;

    // TODO: This is terrible
    Settings::_lerp(lerpSettings.c_timeperiod, _settingsLerp.c_timeperiod);
    Settings::_lerp(lerpSettings.c_temp, _settingsLerp.c_temp);
    Settings::_lerp(lerpSettings.c_airflow, _settingsLerp.c_airflow);

    Settings::_lerp(lerpSettings.f_timeperiod, _settingsLerp.f_timeperiod);
    Settings::_lerp(lerpSettings.f_temp, _settingsLerp.f_temp);
    Settings::_lerp(lerpSettings.f_airflow, _settingsLerp.f_airflow);
    Settings::_lerp(lerpSettings.f_light, _settingsLerp.f_light);

    Settings::_lerp(lerpSettings.d_timeperiod, _settingsLerp.d_timeperiod);
    Settings::_lerp(lerpSettings.d_temp, _settingsLerp.d_temp);
    Settings::_lerp(lerpSettings.d_airflow, _settingsLerp.d_airflow);
}

void Settings::loadSettings(void)
{
    if (FileManager::exists("/settings")){
        FileManager::read("/settings", &settings, sizeof(settings));
    }else{
        // First time create the file
        saveSettings();
    } 

    calcLerpSettings();
}

void Settings::saveSettings(void)
{
    FileManager::write("/settings", &settings, sizeof(settings));
    calcLerpSettings();
}

void Settings::_lerp(uint8_t & setting, Lerp lerp){
    setting = lerp.l_min + (lerp.l_max - lerp.l_min) * (setting / lerp.s_range);
}