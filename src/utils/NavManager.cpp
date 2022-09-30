#include "NavManager.h"

namespace Nav {

Screen* currentScreen = NULL;
Screen* lastScreen    = NULL;

SettingsScreen settings_menu = SettingsScreen(settings_menu_i, settings_menu_il);

NavScreen menu_colonise  = NavScreen(menu_colonise_i, menu_colonise_il, 12, &menu_settings, &menu_mycelium, &colonise_wipe);
NavScreen menu_mycelium  = NavScreen(menu_mycelium_i, menu_mycelium_il, 12, &menu_colonise, &menu_dehydrate, &mycelium_insert);
NavScreen menu_dehydrate = NavScreen(menu_dehydrate_i, menu_dehydrate_il, 12, &menu_mycelium, &menu_settings, NULL);
NavScreen menu_settings  = NavScreen(menu_settings_i, menu_settings_il, 12, &menu_dehydrate, &menu_colonise, &settings_menu);

NavScreen colonise_close      = NavScreen(colonise_close_i, colonise_close_il, 12, &colonise_insert, &colonise_colonising, &help_lid_c); 
NavScreen colonise_colonising = NavScreen(colonise_colonising_i, colonise_colonising_il, 12, NULL, NULL, &menu_colonise); 
NavScreen colonise_inject     = NavScreen(colonise_inject_i, colonise_inject_il, 12, &colonise_wipe, &colonise_insert, &help_inject_c); 
NavScreen colonise_insert     = NavScreen(colonise_insert_i, colonise_insert_il, 12, &colonise_inject, &colonise_close, &help_insert_c); 
NavScreen colonise_wipe       = NavScreen(colonise_wipe_i, colonise_wipe_il, 12, &menu_colonise, &colonise_inject, &help_wipe_c); 

NavScreen mycelium_close    = NavScreen(mycelium_close_i, mycelium_close_il, 12, &colonise_insert, &mycelium_fruiting, &help_lid_m); 
NavScreen mycelium_fruiting = NavScreen(mycelium_fruiting_i, mycelium_fruiting_il, 12, NULL, NULL, &menu_colonise); 
NavScreen mycelium_insert   = NavScreen(mycelium_insert_i, mycelium_insert_il, 12, &menu_mycelium, &mycelium_close, &help_insert_m); 

NavScreen help_inject_c = NavScreen(help_inject_i, help_inject_il, 1, NULL, NULL, &colonise_inject); 
NavScreen help_insert_c = NavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &colonise_insert); 
NavScreen help_lid_c    = NavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &colonise_close); 
NavScreen help_wipe_c   = NavScreen(help_wipe_i, help_wipe_il, 1, NULL, NULL, &colonise_wipe); 

NavScreen help_insert_m = NavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &mycelium_insert); 
NavScreen help_lid_m    = NavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &mycelium_close);

InputScreen settings_c_time    = InputScreen(settings_timeperiod_i, settings_timeperiod_il, &c_timeperiod, 50);
InputScreen settings_c_temp    = InputScreen(settings_temperature_i, settings_temperature_il, &c_temp, 11);
InputScreen settings_c_airflow = InputScreen(settings_airflow_i, settings_airflow_il, &c_airflow, 10);

InputScreen settings_f_time    = InputScreen(settings_timeperiod_i, settings_timeperiod_il, &f_timeperiod, 50);
InputScreen settings_f_temp    = InputScreen(settings_temperature_i, settings_temperature_il, &f_temp, 11);
InputScreen settings_f_airflow = InputScreen(settings_airflow_i, settings_airflow_il, &f_airflow, 10);
InputScreen settings_f_light   = InputScreen(settings_light_i, settings_light_il, &f_light, 10);

void gotoScreen(Screen* screen, bool load){
    if (screen == NULL) {
        return;
    }
    
    currentScreen = screen;

    if (load) { currentScreen->load(); }
}

}