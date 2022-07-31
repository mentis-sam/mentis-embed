#include "TftInfoScreen.h"
#include "Free_Fonts.h"
#include <PNGdec.h>
#include "screen_utils.h"
// #include "qrcode1.h"

PNG png; // PNG decoder inatance

TftInfoScreen::TftInfoScreen(char *title, const unsigned char *qrcode, size_t qrcodeLen, TftScreen *parent)
: TftScreen(title, parent), qrcode(qrcode), qrcodeLen(qrcodeLen)
{
}

#define MAX_IMAGE_WDITH 200

void pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(TFT_HEIGHT - 200, (TFT_WIDTH - 200 )/ 2 + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void TftInfoScreen::render(void)
{
    currentScreen = this;

    tft.fillScreen(TFT_BLACK);
    drawRectStroke(0, (TFT_WIDTH - 200) / 2, TFT_HEIGHT - 200, 70, 5, TFT_WHITE);
    tft.setTextColor(TFT_WHITE);
    tft.setTextFont(4);
    tft.drawCentreString("Back", (TFT_HEIGHT - 200) / 2, 45, 4);
    int16_t rc = png.openFLASH((uint8_t *)qrcode, qrcodeLen, pngDraw);
    if (rc == PNG_SUCCESS) {
        tft.startWrite();
        rc = png.decode(NULL, 0);
        tft.endWrite();
    }

}

void TftInfoScreen::onClick(void)
{
    parent->render();
    // if (highlightedBtn == 0)
    //     cancel->render();
    // else if (highlightedBtn == 1)
    //     ok->render();
    // else
    //     info->render();
}

void TftInfoScreen::onRotation(void)
{
}

void TftInfoScreen::rerender(void)
{
    // // tft.drawRect(0, 170, 106, 70, TFT_WHITE);
    // tft.setTextColor(highlightedBtn == 0 ? TFT_BLACK : TFT_WHITE);       
    // tft.fillRect(0, 170, 106, 70, highlightedBtn == 0 ? TFT_WHITE : TFT_BLACK);
    // tft.drawCentreString("Back", 53 ,195, 4);

    // // tft.drawRect(106, 170, 106, 70, TFT_WHITE);
    // tft.setTextColor(highlightedBtn == 1 ? TFT_BLACK : TFT_WHITE);      
    // tft.fillRect(106, 170, 106, 70, highlightedBtn == 1 ? TFT_WHITE : TFT_BLACK);
    // tft.drawCentreString("OK", 159 ,195, 4);

    // // tft.drawRect(212, 170, 106, 70, TFT_WHITE);
    // tft.setTextColor(highlightedBtn == 2 ? TFT_BLACK : TFT_WHITE);      
    // tft.fillRect(212, 170, 106, 70, highlightedBtn == 2 ? TFT_WHITE : TFT_BLACK);
    // tft.drawCentreString("Info", 265 ,195, 4);
}