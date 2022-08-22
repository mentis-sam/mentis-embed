#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "TFT_eSPI.h"

#include "screens\TftScreen.h"
#include "screens\TftMenuScreen.h"

#include "screen_files\menu_colonise.h"
#include "screen_files\menu_dehydrate.h"
#include "screen_files\menu_mycelium.h"
#include "screen_files\menu_settings.h"

#include "NavScreens.h"

namespace Nav {

extern TftScreen* currentScreen;
extern NavScreen  currentScreenName;// = NavScreen::Colonise;

void gotoScreen(NavScreen screen); 

}


#endif /* NAV_MANAGER */