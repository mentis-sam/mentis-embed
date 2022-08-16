#include "TftSetupScreen.h"
#include "Free_Fonts.h"
#include "screen_utils.h"

#define DISPLAY_WIDTH 20

void drawStringWrapOnWords(char* string, int x, int y)
{
    char copy[255];
    char toPrint[255] = {0};
    int lineLength = 0;
    strcpy(copy, string);
    char* token = strtok(copy, " ");

    while (token != NULL)
    {
        if (strlen(token) + lineLength > DISPLAY_WIDTH)
        {
            tft.drawString(toPrint, x, y, GFXFF);
            y += tft.fontHeight(GFXFF);
            memset(toPrint, 0, sizeof(toPrint));
            lineLength = 0;
        }
        strcat(toPrint, token);
        strcat(toPrint, " ");
        lineLength += strlen(token) + 1;
        token = strtok(NULL,  " ");
    }
    if (lineLength)
    {
        tft.drawString(toPrint, x, y, GFXFF);
    }
}



TftSetupScreen::TftSetupScreen(char *title, char *text, TftScreen *parent)
: TftScreen(title, parent), highlightedBtn(-1)
{
    strcpy(this->text, text);
}

void TftSetupScreen::render(void)
{
    highlightedBtn = 0;
    currentScreen = this;
    g_rotValue = 0;

    tft.setTextDatum(TL_DATUM);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setFreeFont(FSS18);
    drawStringWrapOnWords(text, 10, 10);
    tft.drawCentreString("Back", 53 ,195, 4);
    tft.drawCentreString("OK", 159 ,195, 4);
    tft.drawCentreString("Info", 265 ,195, 4);
    rerender();

}

void TftSetupScreen::nextFrame(void)
{

}

void TftSetupScreen::onClick(void)
{
    if (highlightedBtn == 0)
        cancel->render();
    else if (highlightedBtn == 1)
        ok->render();
    else
        info->render();
}

void TftSetupScreen::onRotation(void)
{
    int toHighlight;
    // Serial.println(g_rotValue);
    if (g_rotValue < 0)
        toHighlight = (255 + g_rotValue) % 3;
    else
        toHighlight = g_rotValue % 3;
    Serial.println(toHighlight);
    if (toHighlight == highlightedBtn)
        return;
    highlightedBtn = toHighlight;
    rerender();
}

void TftSetupScreen::rerender(void)
{

    drawRectStroke(0, 170, 106, 70, 5, highlightedBtn == 0 ? TFT_WHITE : TFT_BLACK);
    drawRectStroke(106, 170, 106, 70, 5, highlightedBtn == 1 ? TFT_WHITE : TFT_BLACK);
    drawRectStroke(212, 170, 106, 70, 5, highlightedBtn == 2 ? TFT_WHITE : TFT_BLACK);
}