#ifndef NAV_SCREEN
#define NAV_SCREEN

#include "modules/screen/ImageScreen.h"
#include "utils/NavManager.h"

class NavScreen: public ImageScreen {
public: 
    Screen* navLeft;
    Screen* navRight;
    Screen* navSelect;

    const uint8_t frames;

    NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames,  Screen* navLeft, Screen* navRight, Screen* navSelect);

    void nextFrame(void);
    void onSelect(void);
    void onLeft(void);
    void onRight(void);
};


#endif /* NAV_SCREEN */
