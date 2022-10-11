#ifndef IMAGE_SCREEN
#define IMAGE_SCREEN

#include <PNGdec.h>

#include "Screen.h"

//extern TFT_eSPI tft;

class ImageScreen: public Screen {
public: 
    ImageScreen(const uint8_t* frame_data, const uint32_t* frame_len);

    void load(void);
    void unload(void);
    void render(void);
    virtual void nextFrame(void) = 0;
    virtual void onSelect(void)  = 0;
    virtual void onLeft(void)    = 0;
    virtual void onRight(void)   = 0;

    // This stops flickering pretty hacky too!!
    static bool _skipRows;
protected:
    const uint8_t*  _frame_d;
    const uint32_t* _frame_l;

    uint8_t _frame;

    
private:
    static void _pngDraw(PNGDRAW *pDraw);
    
};

#endif /* IMAGE_SCREEN */
