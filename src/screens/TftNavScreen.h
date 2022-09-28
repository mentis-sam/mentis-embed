#ifndef TFTMENUSCREEN
#define TFTMENUSCREEN

#include <TFT_eSPI.h>
#include <PNGdec.h>
#include "Free_Fonts.h"

#include "TftScreen.h"

#include "utils/NavManager.h"
#include "utils/screen_utils.h"

extern TFT_eSPI tft;
extern volatile int8_t g_rotValue;

class TftNavScreen: public TftScreen {
public: 
    const uint8_t* frame_d;
    const uint32_t* frame_l;
    const uint8_t frames;

    TftScreen* navLeft;
    TftScreen* navRight;
    TftScreen* navSelect;

    uint8_t frame;

    TftNavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames,  TftScreen* navLeft, TftScreen* navRight, TftScreen* navSelect);

    // void setChoices(TftMenuItem **choices, int len);
    void rerender(void);
    void render(void);
    void nextFrame(void);
    void onClick(void);
    void onRotation(void);
};


#endif /* TFTMENUSCREEN */
