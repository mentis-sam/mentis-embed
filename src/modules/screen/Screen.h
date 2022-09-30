#ifndef SCREEN
#define SCREEN

#define SCREEN_WIDTH TFT_HEIGHT
#define SCREEN_HEIGHT TFT_WIDTH

#include <TFT_eSPI.h>

//extern TFT_eSPI tft;

// TODO: REMOVE NEED TO SET _loaded = false on screen change
// too easy to forget
class Screen {
public:
    Screen();

    static  uint8_t initialise(void);

    virtual void load(void) = 0;
    virtual void render(void) = 0;
    virtual void nextFrame(void) = 0;
    virtual void onSelect(void) = 0;
    virtual void onLeft(void) = 0;
    virtual void onRight(void) = 0;
    
protected:
    bool _loaded;
    static TFT_eSPI tft;
};


#endif /* SCREEN */
