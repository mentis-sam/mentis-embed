#include "NavManager.h"

namespace Nav {

TftScreen* currentScreen = NULL;

TftNavScreen menu_colonise  = TftNavScreen(menu_colonise_i, menu_colonise_il, 12, &menu_settings, &menu_mycelium, &colonise_wipe);
TftNavScreen menu_mycelium  = TftNavScreen(menu_mycelium_i, menu_mycelium_il, 12, &menu_colonise, &menu_dehydrate, &mycelium_insert);
TftNavScreen menu_dehydrate = TftNavScreen(menu_dehydrate_i, menu_dehydrate_il, 12, &menu_mycelium, &menu_settings, NULL);
TftNavScreen menu_settings  = TftNavScreen(menu_settings_i, menu_settings_il, 12, &menu_dehydrate, &menu_colonise, NULL);

TftNavScreen colonise_close      = TftNavScreen(colonise_close_i, colonise_close_il, 12, &colonise_insert, &colonise_colonising, &help_lid_c); 
TftNavScreen colonise_colonising = TftNavScreen(colonise_colonising_i, colonise_colonising_il, 12, NULL, NULL, &menu_colonise); 
TftNavScreen colonise_inject     = TftNavScreen(colonise_inject_i, colonise_inject_il, 12, &colonise_wipe, &colonise_insert, &help_inject_c); 
TftNavScreen colonise_insert     = TftNavScreen(colonise_insert_i, colonise_insert_il, 12, &colonise_inject, &colonise_close, &help_insert_c); 
TftNavScreen colonise_wipe       = TftNavScreen(colonise_wipe_i, colonise_wipe_il, 12, &menu_colonise, &colonise_inject, &help_wipe_c); 

TftNavScreen mycelium_close    = TftNavScreen(mycelium_close_i, mycelium_close_il, 12, &colonise_insert, &mycelium_fruiting, &help_lid_m); 
TftNavScreen mycelium_fruiting = TftNavScreen(mycelium_fruiting_i, mycelium_fruiting_il, 12, NULL, NULL, &menu_colonise); 
TftNavScreen mycelium_insert   = TftNavScreen(mycelium_insert_i, mycelium_insert_il, 12, &menu_mycelium, &mycelium_close, &help_insert_m); 

TftNavScreen help_inject_c = TftNavScreen(help_inject_i, help_inject_il, 1, NULL, NULL, &colonise_inject); 
TftNavScreen help_insert_c = TftNavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &colonise_insert); 
TftNavScreen help_lid_c    = TftNavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &colonise_close); 
TftNavScreen help_wipe_c   = TftNavScreen(help_wipe_i, help_wipe_il, 1, NULL, NULL, &colonise_wipe); 

TftNavScreen help_insert_m = TftNavScreen(help_insert_i, help_insert_il, 1, NULL, NULL, &mycelium_insert); 
TftNavScreen help_lid_m    = TftNavScreen(help_lid_i, help_lid_il, 1, NULL, NULL, &mycelium_close);

void gotoScreen(TftScreen* screen) {
    if (screen == NULL) {
        return;
    }

    currentScreen = screen;
    currentScreen->render();
}

}