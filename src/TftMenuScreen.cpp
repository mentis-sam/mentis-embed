#include "TftMenuScreen.h"
#include "Free_Fonts.h"
#include "screen_utils.h"

// TftMenuItem::TftMenuItem(char *name)
// {
//     strcpy(this->name, name);
// }


void TftMenuScreen::addItem(const char *name, TftScreen *next)
{
    strcpy(choices[nChoices].name, name);
    choices[nChoices].next = next;
    nChoices++;
}


TftMenuScreen::TftMenuScreen(char *title, TftScreen *parent)
: TftScreen(title, parent), highlightedItem(-1), nChoices(0)
{

}

void TftMenuScreen::render(void)
{
    window = 0;
    highlightedItem = 0;
    currentScreen = this;
    g_rotValue = 0;
    tft.fillScreen(TFT_BLACK);
    rerender();
}

void TftMenuScreen::rerender(void)
{
    int a, b;
    if (!(highlightedItem >= window && highlightedItem < window + WINDOW_SIZE)) // if the highlighted item is NOT in the current window
    {
        if (highlightedItem < window)
            window = highlightedItem;
        else
            window = highlightedItem - WINDOW_SIZE + 1;
    }
    // Draw the items in the curretn window
    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        if (i + window == highlightedItem)
        {
            // tft.fillRect(0, i * (SCREEN_HEIGHT / WINDOW_SIZE), SCREEN_WIDTH, (SCREEN_HEIGHT / WINDOW_SIZE), TFT_WHITE);
            tft.setTextPadding(SCREEN_WIDTH);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextDatum(MC_DATUM);
            tft.setFreeFont(FSS18);
            tft.drawString(choices[i + window].name, SCREEN_WIDTH / 2, i * (SCREEN_HEIGHT / WINDOW_SIZE) + (SCREEN_HEIGHT / WINDOW_SIZE) / 2, GFXFF);
            drawRectStroke(0, i * (SCREEN_HEIGHT / WINDOW_SIZE), SCREEN_WIDTH, (SCREEN_HEIGHT / WINDOW_SIZE), 5, TFT_WHITE);
        }
        else
        {
            tft.setTextPadding(SCREEN_WIDTH);
            tft.setTextColor(TFT_WHITE, TFT_BLACK);
            tft.setTextDatum(MC_DATUM);
            tft.setFreeFont(FSS18);
            tft.drawString(choices[i + window].name, SCREEN_WIDTH / 2, i * (SCREEN_HEIGHT / WINDOW_SIZE) + (SCREEN_HEIGHT / WINDOW_SIZE) / 2, GFXFF);
            drawRectStroke(0, i * (SCREEN_HEIGHT / WINDOW_SIZE), SCREEN_WIDTH, (SCREEN_HEIGHT / WINDOW_SIZE), 5, TFT_BLACK);
        }
    }
}

void TftMenuScreen::onRotation(void)
{
    int toHighlight;
    if (g_rotValue < 0)
        g_rotValue += nChoices;

    toHighlight = g_rotValue % nChoices;
    if (toHighlight > nChoices)
        toHighlight = 0;
    if (toHighlight == highlightedItem)
        return;
    highlightedItem = toHighlight;
    Serial.printf("highlighted %d\n", highlightedItem);
    rerender();
}

void TftMenuScreen::onClick(void)
{
    if (choices[highlightedItem].next)
        choices[highlightedItem].next->render();
}
