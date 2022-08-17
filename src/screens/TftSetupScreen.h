#ifndef TFTSETUPSCREEN
#define TFTSETUPSCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

extern TFT_eSPI tft;
extern TftScreen *currentScreen;
extern volatile int8_t g_rotValue;

class TftSetupScreen: TftScreen {
public:
    char text[255];
    TftScreen *ok;
    TftScreen *cancel;
    TftScreen *info;
    int highlightedBtn;

    TftSetupScreen(char *title, char *text);

    void render(void);  
    void rerender(void);
    void nextFrame(void);
    void onClick(void);
    void onRotation(void);
};


#endif /* TFTSETUPSCREEN */

