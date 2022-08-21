#ifndef TFTMENUSCREEN
#define TFTMENUSCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

#include "utils\NavScreens.h"
#include "utils\NavManager.h"
#include "utils\screen_utils.h"

//#include "screen_files\colonise.h"
//#include "screen_files\mycelium.h"
//#include "screen_files\dehydrate.h"
//#include "screen_files\settings.h"

extern TFT_eSPI tft;
extern volatile int8_t g_rotValue;

class TftMenuScreen: public TftScreen {
public: 
    NavScreen menuScreen;

    //const uint8_t* screens_d;
    const uint8_t* frame_d;
    const uint32_t* frame_l;

    NavScreen navLeft;
    NavScreen navRight;
    NavScreen navSelect;

    int frame;

    TftMenuScreen(NavScreen screen, const uint8_t* frame_data, const uint32_t frame_len[12],  NavScreen navLeft, NavScreen navRight, NavScreen navSelect);

    // void setChoices(TftMenuItem **choices, int len);
    void rerender(void);
    void render(void);
    void nextFrame(void);
    void onClick(void);
    void onRotation(void);
    
};


#endif /* TFTMENUSCREEN */
