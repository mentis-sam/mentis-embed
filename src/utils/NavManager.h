#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "TFT_eSPI.h"

#include "screens\TftMenuScreen.h"
#include "screens\TftScreen.h"

#include "screen_files\menu_colonise.h"
#include "screen_files\menu_dehydrate.h"
#include "screen_files\menu_mycelium.h"
#include "screen_files\menu_settings.h"

#include "NavScreens.h"

class TftMenuScreen;

namespace Nav {

extern TftScreen* currentScreen;

extern TftMenuScreen menu_colonise;
extern TftMenuScreen menu_mycelium;
extern TftMenuScreen menu_dehydrate;
extern TftMenuScreen menu_settings;

void gotoScreen(TftScreen* screen); 

}


#endif /* NAV_MANAGER */