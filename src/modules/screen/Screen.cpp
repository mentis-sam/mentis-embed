#include "Screen.h"

TFT_eSPI Screen::tft = TFT_eSPI();

Screen::Screen(void): _loaded(false)
{
}

uint8_t Screen::initialise(void)
{
    // TODO: Add debugging
    tft.init();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);

    Serial.println("ScreenModule: Initialised\n");

    return 0;
}

// TODO: Define load function here not in ImageScreen