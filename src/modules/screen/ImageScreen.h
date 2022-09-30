#ifndef IMAGE_SCREEN
#define IMAGE_SCREEN

#include <PNGdec.h>

#include "Screen.h"

//extern TFT_eSPI tft;

class ImageScreen: public Screen {
public: 
    const uint8_t* frame_d;
    const uint32_t* frame_l;

    uint8_t frame;
    
    ImageScreen(const uint8_t* frame_data, const uint32_t* frame_len);

    void load(void);
    void render(void);
    virtual void nextFrame(void) = 0;
    virtual void onSelect(void)  = 0;
    virtual void onLeft(void)    = 0;
    virtual void onRight(void)   = 0;
private:
    static  void _pngDraw(PNGDRAW *pDraw);
};

#endif /* IMAGE_SCREEN */
