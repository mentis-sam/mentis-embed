#ifndef NAV_SCREEN
#define NAV_SCREEN

#include "utils/screen/ImageScreen.h"
#include "utils/NavManager.h"

class NavScreen: public ImageScreen {
public: 
    NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames,  Screen* navLeft, Screen* navRight, Screen* navSelect, void (*loadCallback)() = [](){}, void (*renderCallback)() = [](){});

    // TODO: implement load -> function to be called passed by ref to start states

    void load(void);
    void nextFrame(void);
    void render(void);
    void onSelect(void);
    void onLeft(void);
    void onRight(void);

private:
    Screen* _navLeft;
    Screen* _navRight;
    Screen* _navSelect;

    void (*_loadCallback)();
    void (*_renderCallback)();

    const uint8_t _frames;
};


#endif /* NAV_SCREEN */
