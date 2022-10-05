#include "settings.h"


// FIXME: Works but should probs refactor this whole thing
const Settings_S Settings::_f_settings = {
    .c_timeperiod = 5,
    .c_temp = 6,
    .c_airflow = 2,

    .f_timeperiod = 4,
    .f_temp = 3,
    .f_airflow = 4,
    .f_light = 4,

    .d_timeperiod = 2,
    .d_temp = 10,

    .beep = 0
};

Settings_S Settings::settings = Settings::_f_settings;

Settings_S Settings::lerpSettings = Settings::settings;

const Settings_Lerp Settings::_settingsLerp = {
    .c_timeperiod = { .s_range = 9, .l_min = 84, .l_max = 672},
    .c_temp = { .s_range = 11, .l_min = 20, .l_max = 31},
    .c_airflow = { .s_range = 50, .l_min = 1, .l_max = 10},

    .f_timeperiod = {.s_range = 14, .l_min = 24, .l_max = 336},
    .f_temp = { .s_range = 11, .l_min = 20, .l_max = 31},
    .f_airflow = { .s_range = 9, .l_min = 1, .l_max = 10},
    .f_light = { .s_range = 10, .l_min = 1, .l_max = 16},

    .d_timeperiod = { .s_range = 5, .l_min = 6, .l_max = 32},
    .d_temp = { .s_range = 11, .l_min = 30, .l_max = 51},
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
}

void Settings::loadSettings(void)
{
    if (FileManager::exists("/settings")){
        FileManager::read("/settings", &Settings::settings, sizeof(Settings::settings));
    }else{
        // First time create the file
        saveSettings();
    } 

    calcLerpSettings();
}

void Settings::saveSettings(void)
{
    FileManager::write("/settings", &Settings::settings, sizeof(Settings::settings));
    calcLerpSettings();
}

void Settings::factory_reset(void){
    Settings::settings = Settings::_f_settings;
}

void Settings::_lerp(uint16_t & setting, Lerp lerp){
    setting = lerp.l_min + (lerp.l_max - lerp.l_min) * (static_cast<float>(setting) / (lerp.s_range));
}