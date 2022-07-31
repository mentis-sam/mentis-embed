#ifndef TFTTEMPERATURESCREEN
#define TFTTEMPERATURESCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

extern TFT_eSPI tft;
extern TftScreen *currentScreen;
extern volatile int8_t g_rotValue;

class TftTemperatureScreen: TftScreen {
public:
    float temperature;

    TftTemperatureScreen(char *title, TftScreen *parent);

    void render(void);  
    void rerender(void);
    void onClick(void);
    void onRotation(void);
};

#endif /* TFTTEMPERATURESCREEN */
