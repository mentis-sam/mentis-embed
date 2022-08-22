#include "NavManager.h"

namespace Nav {

TftScreen* currentScreen = new TftMenuScreen(menu_colonise, menu_colonise_l, 12, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
NavScreen currentScreenName = NavScreen::Colonise;

void gotoScreen(NavScreen screen) {
    if (screen == currentScreenName){
        return;
    }

    delete currentScreen;
    //currentScreen = &menuColoniseScreen;
    currentScreenName = screen;
    
    switch (screen) {
        case NavScreen::Colonise:
            currentScreen = new TftMenuScreen(menu_colonise, menu_colonise_l, 12, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
            break;
        case NavScreen::Mycelium:
            currentScreen = new TftMenuScreen(menu_mycelium, menu_mycelium_l, 12, NavScreen::Colonise, NavScreen::Dehydrate, NavScreen::Dehydrate);
            break;
        case NavScreen::Dehydrate:
            currentScreen = new TftMenuScreen(menu_dehydrate, menu_dehydrate_l, 12, NavScreen::Mycelium, NavScreen::Settings, NavScreen::Dehydrate);
            break;
        case NavScreen::Settings:
            currentScreen = new TftMenuScreen(menu_settings, menu_settings_l, 12, NavScreen::Dehydrate, NavScreen::Colonise, NavScreen::Dehydrate);
            break;
    }

   currentScreen->render();
}

}