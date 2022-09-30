#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "modules/screen/NavScreen.h"
#include "modules/screen/SettingsScreen.h"
//#include "modules/screen/Screen.h"

#include "screen_files/menu_colonise.h"
#include "screen_files/menu_dehydrate.h"
#include "screen_files/menu_mycelium.h"
#include "screen_files/menu_settings.h"

#include "screen_files/colonise_close.h"
#include "screen_files/colonise_colonising.h"
#include "screen_files/colonise_inject.h"
#include "screen_files/colonise_insert.h"
#include "screen_files/colonise_wipe.h"

#include "screen_files/mycelium_close.h"
#include "screen_files/mycelium_fruiting.h"
#include "screen_files/mycelium_insert.h"

#include "screen_files/help_inject.h"
#include "screen_files/help_insert.h"
#include "screen_files/help_lid.h"
#include "screen_files/help_wipe.h"

#include "screen_files/settings_menu.h"

class NavScreen;
class SettingsScreen;
//class Screen;

namespace Nav {

extern Screen* currentScreen;

extern NavScreen menu_colonise;
extern NavScreen menu_mycelium;
extern NavScreen menu_dehydrate;
extern NavScreen menu_settings;

extern NavScreen colonise_close;
extern NavScreen colonise_colonising;
extern NavScreen colonise_inject;
extern NavScreen colonise_insert;
extern NavScreen colonise_wipe;

extern NavScreen mycelium_close;
extern NavScreen mycelium_fruiting;
extern NavScreen mycelium_insert;

extern NavScreen help_inject_c;
extern NavScreen help_insert_c;
extern NavScreen help_lid_c;
extern NavScreen help_wipe_c;

// Create multiples so that help returns to the correct screen
// this could definately be done better
extern NavScreen help_insert_m;
extern NavScreen help_lid_m;

extern SettingsScreen screen_menu;

void gotoScreen(Screen* screen, bool load = true); 

}


#endif /* NAV_MANAGER */