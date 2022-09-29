#ifndef TFTSCREEN
#define TFTSCREEN

#include <TFT_eSPI.h>

#define WINDOW_SIZE 3
#define SCREEN_WIDTH TFT_HEIGHT
#define SCREEN_HEIGHT TFT_WIDTH

class TftScreen {
public:

    TftScreen();
    virtual void load(void) = 0;
    //virtual void unload(void) = 0;

    virtual void render(void) = 0;
    virtual void nextFrame(void) = 0;
    virtual void onClick(void) = 0;
    virtual void onLeft(void) = 0;
    virtual void onRight(void) = 0;
protected:
    bool _loaded;
};


#endif /* TFTSCREEN */
