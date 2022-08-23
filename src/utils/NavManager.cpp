#include "NavManager.h"

namespace Nav {

TftScreen* currentScreen = NULL;

TftMenuScreen menu_colonise  = TftMenuScreen(menu_colonise_i, menu_colonise_il, 12, &Nav::menu_settings, &Nav::menu_mycelium, &Nav::menu_colonise);
TftMenuScreen menu_mycelium  = TftMenuScreen(menu_mycelium_i, menu_mycelium_il, 12, &Nav::menu_colonise, &Nav::menu_dehydrate, &Nav::menu_colonise);
TftMenuScreen menu_dehydrate = TftMenuScreen(menu_dehydrate_i, menu_dehydrate_il, 12, &Nav::menu_mycelium, &Nav::menu_settings, &Nav::menu_colonise);
TftMenuScreen menu_settings  = TftMenuScreen(menu_settings_i, menu_settings_il, 12, &Nav::menu_colonise, &Nav::menu_colonise, &Nav::menu_colonise);

void gotoScreen(TftScreen* screen) {
    currentScreen = screen;

   currentScreen->render();
}

}