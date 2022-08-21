#include "NavManager.h"

namespace Nav {

TftScreen* currentScreen = new TftMenuScreen(NavScreen::Colonise, dehydrate, dehydrate_l, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
NavScreen currentScreenName = NavScreen::Colonise;

//TftMenuScreen menuColoniseScreen    = TftMenuScreen(NavScreen::Colonise, dehydrate, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
//TftMenuScreen menuMyceliumScreen    = TftMenuScreen(NavScreen::Mycelium, NavScreen::Colonise, NavScreen::Dehydrate, NavScreen::Dehydrate);
//TftMenuScreen menuDehydrateScreen   = TftMenuScreen(NavScreen::Dehydrate, NavScreen::Mycelium, NavScreen::Settings, NavScreen::Dehydrate);
//TftMenuScreen menuSettingsScreen    = TftMenuScreen(NavScreen::Settings, NavScreen::Dehydrate, NavScreen::Colonise, NavScreen::Dehydrate);

void gotoScreen(NavScreen screen) {
    if (screen == currentScreenName){
        return;
    }

    //currentScreen = &menuColoniseScreen;
    //currentScreenName = screen;
    
    switch (screen) {
        case NavScreen::Colonise:
            //currentScreen = new TftMenuScreen(NavScreen::Colonise, NavScreen::Settings, NavScreen::Mycelium, NavScreen::Dehydrate);
            break;
        case NavScreen::Mycelium:
            //currentScreen = new TftMenuScreen( NavScreen::Mycelium, NavScreen::Colonise, NavScreen::Dehydrate, NavScreen::Dehydrate);
            break;
        case NavScreen::Dehydrate:
            //currentScreen = new TftMenuScreen(NavScreen::Dehydrate, NavScreen::Mycelium, NavScreen::Settings, NavScreen::Dehydrate);
            break;
        case NavScreen::Settings:
            //currentScreen = new TftMenuScreen(NavScreen::Settings, NavScreen::Dehydrate, NavScreen::Colonise, NavScreen::Dehydrate);
            break;
    }

   currentScreen->render();
}

}