#ifndef NAV_MANAGER_H
#define NAV_MANAGER_H

#include "TFT_eSPI.h"

#include "screens\TftScreen.h"
#include "screens\TftMenuScreen.h"

#include "NavScreens.h"

extern TftScreen* currentScreen;// = new TftMenuScreen(NavScreen::Colonise, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
extern NavScreen  currentScreenName;// = NavScreen::Colonise;

void gotoScreen(NavScreen screen);  


#endif /* NAV_MANAGER */