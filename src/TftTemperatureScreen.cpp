#include "TftTemperatureScreen.h"
#include "Free_Fonts.h"
#include "screen_utils.h"

TftTemperatureScreen::TftTemperatureScreen(char *title, TftScreen *parent)
: TftScreen(title, parent), temperature(0)
{
}


void TftTemperatureScreen::render(void)
{
    currentScreen = this;

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.setFreeFont(FSS18);
    tft.drawString("Temperature", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6, GFXFF);

    // tft.fillRect(0, 2 * (SCREEN_HEIGHT / 3), SCREEN_WIDTH, SCREEN_HEIGHT / 3, TFT_WHITE);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Back", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 6) * 5, GFXFF);
    drawRectStroke(0, 2 * (SCREEN_HEIGHT / 3), SCREEN_WIDTH, SCREEN_HEIGHT / 3, 5, TFT_WHITE);

    tft.setTextDatum(ML_DATUM);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("C", (SCREEN_WIDTH / 3) * 2, SCREEN_HEIGHT / 2, GFXFF);

    rerender();
}

void TftTemperatureScreen::onClick(void)
{
    parent->render();
}

void TftTemperatureScreen::onRotation(void)
{
}

void TftTemperatureScreen::rerender(void)
{
    static char s[10];

    sprintf(s, "%.1f", temperature);
    tft.setTextPadding(50);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(s, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GFXFF);
}