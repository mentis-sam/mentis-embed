#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "TFT_eSPI.h"

#include "screens/TftNavScreen.h"
#include "screens/TftScreen.h"

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

class TftNavScreen;

namespace Nav {

extern TftScreen* currentScreen;

extern TftNavScreen menu_colonise;
extern TftNavScreen menu_mycelium;
extern TftNavScreen menu_dehydrate;
extern TftNavScreen menu_settings;

extern TftNavScreen colonise_close;
extern TftNavScreen colonise_colonising;
extern TftNavScreen colonise_inject;
extern TftNavScreen colonise_insert;
extern TftNavScreen colonise_wipe;

extern TftNavScreen mycelium_close;
extern TftNavScreen mycelium_fruiting;
extern TftNavScreen mycelium_insert;

extern TftNavScreen help_inject_c;
extern TftNavScreen help_insert_c;
extern TftNavScreen help_lid_c;
extern TftNavScreen help_wipe_c;

// Create multiples so that help returns to the correct screen
// this could definately be done better
extern TftNavScreen help_insert_m;
extern TftNavScreen help_lid_m;

void gotoScreen(TftScreen* screen); 

}


#endif /* NAV_MANAGER */