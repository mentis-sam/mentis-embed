#ifndef TFTINFOSCREEN
#define TFTINFOSCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

extern TFT_eSPI tft;
extern TftScreen *currentScreen;
extern volatile int8_t g_rotValue;

class TftInfoScreen: TftScreen {
public:
    const unsigned char *qrcode;
    size_t qrcodeLen;

    TftInfoScreen(char *title, const unsigned char *qrcode, size_t qrcodeLen, TftScreen *parent);

    void render(void);  
    void rerender(void);
    void nextFrame(void);
    void onClick(void);
    void onRotation(void);
};

#endif /* TFTINFOSCREEN */
