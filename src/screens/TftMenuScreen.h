#ifndef TFTMENUSCREEN
#define TFTMENUSCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

#include "utils\NavScreens.h"
#include "utils\NavManager.h"
#include "utils\screen_utils.h"

#include "screen_files\colonise.h"
#include "screen_files\mycelium.h"
#include "screen_files\dehydrate.h"
#include "screen_files\settings.h"

extern TFT_eSPI tft;
extern volatile int8_t g_rotValue;

class TftMenuScreen: public TftScreen {
public: 
    NavScreen menuScreen;

    NavScreen navLeft;
    NavScreen navRight;
    NavScreen navSelect;

    int frame;

    TftMenuScreen(NavScreen screen, NavScreen navLeft, NavScreen navRight, NavScreen navSelect);

    // void setChoices(TftMenuItem **choices, int len);
    void rerender(void);
    void render(void);
    void nextFrame(void);
    void onClick(void);
    void onRotation(void);
    
};


#endif /* TFTMENUSCREEN */
