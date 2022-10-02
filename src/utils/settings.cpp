#include "settings.h"

Settings settings = {
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

void loadSettings(void)
{
    if (FileManager::exists("/settings")){
        FileManager::read("/settings", &settings, sizeof(settings));
    }else{
        // First time create the file
        saveSettings();
    }
    
}

void saveSettings(void)
{
    FileManager::write("/settings", &settings, sizeof(settings));
}