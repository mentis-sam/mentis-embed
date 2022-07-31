#ifndef TFTSCREEN
#define TFTSCREEN

#include <TFT_eSPI.h>

#define WINDOW_SIZE 3
#define SCREEN_WIDTH TFT_HEIGHT
#define SCREEN_HEIGHT TFT_WIDTH

class TftScreen {
public:
    char title[255];
    TftScreen *parent;

    TftScreen(char *title, TftScreen *parent);
    virtual void render(void) = 0;
    virtual void rerender(void) = 0;
    virtual void onClick(void) = 0;
    virtual void onRotation(void) = 0;
   
};


#endif /* TFTSCREEN */
