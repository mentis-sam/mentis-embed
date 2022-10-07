#include "NavManager.h"



namespace Nav {

Screen* currentScreen = NULL;
Screen* lastScreen    = NULL;

uint32_t lastTimeLeft = 0;
void daysRemaining(void) {
    uint32_t timeLeft =  ((MachineState::getTimeLeft() + 24)/24);

    ImageScreen::_skipRows = true;
    char str[255]; 
    sprintf(str, "%d days remaining", ((MachineState::getTimeLeft() + 24)/24));
    Screen::tft.drawString(str, SCREEN_WIDTH/2 + 8, 40);

    if (timeLeft != lastTimeLeft) {
        ImageScreen::_skipRows = false;
    }

    lastTimeLeft = timeLeft;
    /*
    uint32_t timeLeft = ((MachineState::getTimeLeft() + 24)/24);

    // Redraw whole screen
    if (lastTimeLeft != timeLeft){
        ImageScreen::_skipRows = false; 
        return;
    }

    //Wait one frame then draw text & stop redrawing top half of screen
    if ((lastTimeLeft != timeLeft) && ImageScreen::_skipRows == false){
        char str[255]; 
        sprintf(str, "%d days remaining", ((MachineState::getTimeLeft() + 24)/24));
        Screen::tft.drawString(str, SCREEN_WIDTH/2 + 8, 40);
        ImageScreen::_skipRows = true; 
        lastTimeLeft = timeLeft;
    }
    */
};

void hoursRemaining(void) {
    uint32_t timeLeft =  MachineState::getTimeLeft();

    ImageScreen::_skipRows = true; 
    char str[255]; 
    sprintf(str, "%d hours remaining", MachineState::getTimeLeft());
    Screen::tft.drawString(str, SCREEN_WIDTH/2 + 8, 40);

    if (timeLeft != lastTimeLeft) {
        ImageScreen::_skipRows = false;
    }

    lastTimeLeft = timeLeft;

    /*
    uint32_t timeLeft =  MachineState::getTimeLeft();

    // Redraw whole screen
    if (lastTimeLeft != timeLeft){
        ImageScreen::_skipRows = false; 
        return;
    }

    //Wait one frame then draw text & stop redrawing top half of screen
    if ((lastTimeLeft != timeLeft) && ImageScreen::_skipRows == false){
        char str[255]; 
        sprintf(str, "%d hours remaining", MachineState::getTimeLeft());
        Screen::tft.drawString(str, SCREEN_WIDTH/2 + 8, 40);
        ImageScreen::_skipRows = true; 
        lastTimeLeft = timeLeft;
    }
    */
};

// How not to implement a menu system lol

SettingsScreen settings_menu = SettingsScreen(settings_menu_i, settings_menu_il);

NavScreen menu_colonise  = NavScreen(menu_colonise_i, menu_colonise_il, 12, &menu_settings, &menu_mycelium, &colonise_wipe);
NavScreen menu_mycelium  = NavScreen(menu_mycelium_i, menu_mycelium_il, 12, &menu_colonise, &menu_dehydrate, &mycelium_insert);
NavScreen menu_dehydrate = NavScreen(menu_dehydrate_i, menu_dehydrate_il, 12, &menu_mycelium, &menu_settings, &dehydrate_dehydrating);
NavScreen menu_settings  = NavScreen(menu_settings_i, menu_settings_il, 12, &menu_dehydrate, &menu_colonise, &settings_menu);

NavScreen colonise_close      = NavScreen(colonise_close_i, colonise_close_il, 12, &colonise_insert, &colonise_ready, &help_lid_c); 
NavScreen colonise_colonising = NavScreen(colonise_colonising_i, colonise_colonising_il, 12, NULL, NULL, &colonise_cancel, []() {MachineState::startState(colonisation, &Settings::lerpSettings.c_timeperiod);}, daysRemaining); 
NavScreen colonise_inject     = NavScreen(colonise_inject_i, colonise_inject_il, 12, &colonise_wipe, &colonise_insert, &help_inject_c); 
NavScreen colonise_insert     = NavScreen(colonise_insert_i, colonise_insert_il, 12, &colonise_inject, &colonise_close, &help_insert_c); 
NavScreen colonise_wipe       = NavScreen(colonise_wipe_i, colonise_wipe_il, 12, &menu_colonise, &colonise_inject, &help_wipe_c); 
NavScreen colonise_ready      = NavScreen(ready_i, ready_il, 12, &colonise_close, NULL, &colonise_colonising); 
CancelScreen colonise_cancel  = CancelScreen(colonise_cancel_i, colonise_cancel_il, &colonise_colonising, &menu_colonise, []() {MachineState::startState(none);});

NavScreen mycelium_close     = NavScreen(mycelium_close_i, mycelium_close_il, 12, &colonise_insert, &mycelium_ready, &help_lid_m); 
NavScreen mycelium_fruiting  = NavScreen(mycelium_fruiting_i, mycelium_fruiting_il, 12, NULL, NULL, &mycelium_cancel, []() {MachineState::startState(fruiting, &Settings::lerpSettings.f_timeperiod);}, daysRemaining); 
NavScreen mycelium_complete  = NavScreen(mycelium_harvest_i, mycelium_harvest_il, 12, NULL, NULL, &menu_mycelium, []() {MachineState::startState(none);});
NavScreen mycelium_ready     = NavScreen(ready_i, ready_il, 12, &mycelium_close, NULL, &mycelium_fruiting); 
NavScreen mycelium_insert    = NavScreen(mycelium_insert_i, mycelium_insert_il, 12, &menu_mycelium, &mycelium_close, &help_insert_m); 
CancelScreen mycelium_cancel = CancelScreen(mycelium_cancel_i, mycelium_cancel_il, &mycelium_fruiting, &menu_mycelium, []() {MachineState::startState(none);});

NavScreen dehydrate_dehydrating = NavScreen(dehydrate_dehydrating_i, dehydrate_dehydrating_il, 12, NULL, NULL, &dehydrate_cancel, []() {MachineState::startState(dehydration, &Settings::lerpSettings.d_timeperiod);}, hoursRemaining);
NavScreen dehydrate_complete    = NavScreen(dehydrate_complete_i, dehydrate_complete_il, 12, NULL, NULL, &menu_dehydrate, []() {MachineState::startState(none);});
CancelScreen dehydrate_cancel   = CancelScreen(dehydrate_cancel_i, dehydrate_cancel_il, &dehydrate_dehydrating, &menu_dehydrate, []() {MachineState::startState(none);});

NavScreen help_inject_c = NavScreen(help_inject_i, help_inject_il, 1, NULL, NULL, &colonise_inject); 
NavScreen help_insert_c = NavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &colonise_insert); 
NavScreen help_lid_c    = NavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &colonise_close); 
NavScreen help_wipe_c   = NavScreen(help_wipe_i, help_wipe_il, 1, NULL, NULL, &colonise_wipe); 

NavScreen help_insert_m = NavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &mycelium_insert); 
NavScreen help_lid_m    = NavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &mycelium_close);

CancelScreen settings_factory_rs = CancelScreen(settings_factory_rs_i, settings_factory_rs_il, &settings_menu, &settings_menu, []() {Settings::factory_reset();});

InputScreen settings_c_time    = InputScreen(settings_timeperiod_c_i, settings_timeperiod_c_il, &Settings::settings.c_timeperiod, 8);
InputScreen settings_c_temp    = InputScreen(settings_temperature_cf_i, settings_temperature_cf_il, &Settings::settings.c_temp, 11);
InputScreen settings_c_airflow = InputScreen(settings_airflow_i, settings_airflow_il, &Settings::settings.c_airflow, 10);

InputScreen settings_f_time    = InputScreen(settings_timeperiod_f_i, settings_timeperiod_f_il, &Settings::settings.f_timeperiod, 14);
InputScreen settings_f_temp    = InputScreen(settings_temperature_cf_i, settings_temperature_cf_il, &Settings::settings.f_temp, 11);
InputScreen settings_f_airflow = InputScreen(settings_airflow_i, settings_airflow_il, &Settings::settings.f_airflow, 10);
InputScreen settings_f_light   = InputScreen(settings_light_i, settings_light_il, &Settings::settings.f_light, 10);

InputScreen settings_d_time = InputScreen(settings_timeperiod_d_i, settings_timeperiod_d_il, &Settings::settings.d_timeperiod, 5);
InputScreen settings_d_temp = InputScreen(settings_temperature_d_i, settings_temperature_d_il, &Settings::settings.d_temp, 11);

void gotoScreen(Screen* screen, bool load){
    if (screen == NULL) {
        return;
    }
    if (currentScreen != NULL){
        currentScreen->unload();
    }
    
    currentScreen = screen;
    if (load) { currentScreen->load(); }
}

}