#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "modules/screen/NavScreen.h"
#include "modules/screen/SettingsScreen.h"
#include "modules/screen/InputScreen.h"
#include "modules/screen/CancelScreen.h"

#include "utils/settings.h"
#include "utils/MachineState.h"

#include "screen_files/menu_colonise.h"
#include "screen_files/menu_dehydrate.h"
#include "screen_files/menu_mycelium.h"
#include "screen_files/menu_settings.h"

#include "screen_files/colonise_close.h"
#include "screen_files/colonise_colonising.h"
#include "screen_files/colonise_inject.h"
#include "screen_files/colonise_insert.h"
#include "screen_files/colonise_wipe.h"
#include "screen_files/colonise_cancel.h"

#include "screen_files/mycelium_close.h"
#include "screen_files/mycelium_fruiting.h"
#include "screen_files/mycelium_insert.h"
#include "screen_files/mycelium_harvest.h"
#include "screen_files/mycelium_cancel.h"

#include "screen_files/dehydrate_dehydrating.h"
#include "screen_files/dehydrate_complete.h"
#include "screen_files/dehydrate_cancel.h"

#include "screen_files/help_inject.h"
#include "screen_files/help_insert.h"
#include "screen_files/help_lid.h"
#include "screen_files/help_wipe.h"

#include "screen_files/settings_menu.h"

#include "screen_files/settings_timeperiod_c.h"
#include "screen_files/settings_timeperiod_d.h"
#include "screen_files/settings_timeperiod_f.h"

#include "screen_files/settings_temperature_cf.h"
#include "screen_files/settings_temperature_d.h"

#include "screen_files/settings_airflow.h"
#include "screen_files/settings_light.h"

#include "screen_files/ready.h"

class NavScreen;
class SettingsScreen;
class InputScreen;
class CancelScreen;
//class Screen;

namespace Nav {

extern Screen* currentScreen;
extern Screen* lastScreen;

extern NavScreen menu_colonise;
extern NavScreen menu_mycelium;
extern NavScreen menu_dehydrate;
extern NavScreen menu_settings;

extern NavScreen colonise_close;
extern NavScreen colonise_colonising;
extern NavScreen colonise_inject;
extern NavScreen colonise_insert;
extern NavScreen colonise_wipe;
extern NavScreen colonise_ready;
extern CancelScreen colonise_cancel;

extern NavScreen mycelium_close;
extern NavScreen mycelium_fruiting;
extern NavScreen mycelium_insert;
extern NavScreen mycelium_complete;
extern NavScreen mycelium_ready;
extern CancelScreen mycelium_cancel;

extern NavScreen help_inject_c;
extern NavScreen help_insert_c;
extern NavScreen help_lid_c;
extern NavScreen help_wipe_c;

extern NavScreen dehydrate_dehydrating;
extern CancelScreen dehydrate_cancel;
extern NavScreen dehydrate_complete;

// Create multiples so that help returns to the correct screen
// this could definately be done better
extern NavScreen help_insert_m;
extern NavScreen help_lid_m;

extern SettingsScreen settings_menu;

extern InputScreen settings_c_time;
extern InputScreen settings_c_temp;
extern InputScreen settings_c_airflow;

extern InputScreen settings_f_time;
extern InputScreen settings_f_temp;
extern InputScreen settings_f_airflow;
extern InputScreen settings_f_light;

extern InputScreen settings_d_time;
extern InputScreen settings_d_temp;

void gotoScreen(Screen* screen, bool load = true); 
void back(bool load = true);

}


#endif /* NAV_MANAGER */