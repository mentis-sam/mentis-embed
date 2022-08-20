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
: TftScreen(), menuScreen(screen), navLeft(navLeft), navRight(navRight), navSelect(navSelect)
{
    // The byte order can be swapped (set true for TFT_eSPI)
    TJpgDec.setSwapBytes(true);

    // The jpeg decoder must be given the exact name of the rendering function above
    TJpgDec.setCallback(tft_output);

}

void TftMenuScreen::render(void)
{
    frame = 0;
    g_rotValue = 0;
    //tft.fillScreen(TFT_BLACK);
    //this->onRotation();
    rerender();
}

void TftMenuScreen::rerender(void)
{
    switch (menuScreen) {
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
    if (g_rotValue < 0){
        Nav::gotoScreen(navLeft);
    }else if (g_rotValue > 0){
        Nav::gotoScreen(navRight);
    }
}

void TftMenuScreen::onClick(void)
{
    Nav::gotoScreen(navSelect);
}
