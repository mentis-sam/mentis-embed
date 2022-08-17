#include "TftMenuScreen.h"
#include "Free_Fonts.h"


#include <TJpg_Decoder.h>

// =======================================================================================
// This function will be called during decoding of the jpeg file
// =======================================================================================
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

/*
void TftMenuScreen::addItem(const char *name, TftScreen *next)
{
    strcpy(choices[nChoices].name, name);
    choices[nChoices].next = next;
    nChoices++;
}
*/

TftMenuScreen::TftMenuScreen(NavScreen screen, NavScreen navLeft, NavScreen navRight, NavScreen navSelect)
: TftScreen(), menuPage(screen)
{
    // The byte order can be swapped (set true for TFT_eSPI)
    TJpgDec.setSwapBytes(true);

    // The jpeg decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);
}

void TftMenuScreen::render(void)
{
    g_rotValue = 0;
    frame = 0;
    
    tft.fillScreen(TFT_BLACK);

    rerender();
}

void TftMenuScreen::rerender(void)
{
    switch (menuPage) {
        case NavScreen::Colonise:
            TJpgDec.drawJpg(0, 0, colonise0, sizeof(colonise0));
            break;
        case NavScreen::Mycelium:
            TJpgDec.drawJpg(0, 0, mycelium0, sizeof(mycelium0));
            break;
        case NavScreen::Dehydrate:
            TJpgDec.drawJpg(0, 0, dehydrate0, sizeof(dehydrate0));
            break;
        case NavScreen::Settings:
            TJpgDec.drawJpg(0, 0, settings0, sizeof(settings0));
            break;
    }
    /*
    switch (frame) {
        case 0:
            TJpgDec.drawJpg(0, 0, dehydrate0, sizeof(dehydrate0));
        case 1:
            TJpgDec.drawJpg(0, 0, dehydrate1, sizeof(dehydrate1));
        case 2:
            TJpgDec.drawJpg(0, 0, dehydrate2, sizeof(dehydrate2));
        case 3:
            TJpgDec.drawJpg(0, 0, dehydrate3, sizeof(dehydrate3));
        case 4:
            TJpgDec.drawJpg(0, 0, dehydrate4, sizeof(dehydrate4));
        case 5:
            TJpgDec.drawJpg(0, 0, dehydrate5, sizeof(dehydrate5));
        case 6:
            TJpgDec.drawJpg(0, 0, dehydrate6, sizeof(dehydrate6));
        case 7:
            TJpgDec.drawJpg(0, 0, dehydrate7, sizeof(dehydrate7));
        case 8:
            TJpgDec.drawJpg(0, 0, dehydrate8, sizeof(dehydrate8));
        case 9:
            TJpgDec.drawJpg(0, 0, dehydrate9, sizeof(dehydrate9));
        case 10:
            TJpgDec.drawJpg(0, 0, dehydrate10, sizeof(dehydrate10));
        case 11:
            TJpgDec.drawJpg(0, 0, dehydrate11, sizeof(dehydrate11));
    }
    */
    /*
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
    */
}

void TftMenuScreen::nextFrame(void)
{
    frame += 1;
    if (frame == 13){
        frame = 0;
    }
    //rerender();
}

void TftMenuScreen::onRotation(void)
{
    int toHighlight;
    Serial.println(g_rotValue);
    //if (g_rotValue < 0)
        //g_rotValue += nChoices;

    //toHighlight = g_rotValue % nChoices;
    //if (toHighlight > nChoices)
    //    toHighlight = 0;
    //if (toHighlight == highlightedItem)
    //    return;
    //highlightedItem = toHighlight;
    //Serial.printf("highlighted %d\n", highlightedItem);
    //rerender();
}

void TftMenuScreen::onClick(void)
{

}
