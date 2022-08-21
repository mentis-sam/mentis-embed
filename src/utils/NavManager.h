#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "TFT_eSPI.h"

#include "screens\TftScreen.h"
#include "screens\TftMenuScreen.h"

#include "screen_files\dehydrate.h"

#include "NavScreens.h"

namespace Nav {

extern TftScreen* currentScreen;// = new TftMenuScreen(NavScreen::Colonise, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
extern NavScreen  currentScreenName;// = NavScreen::Colonise;

void gotoScreen(NavScreen screen); 

}


#endif /* NAV_MANAGER */