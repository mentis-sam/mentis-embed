#include "screen_utils.h"

void drawRectStroke(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t stroke, uint32_t color) {
    for (int i = 0; i < stroke; i++)
    {
        tft.drawRect(x + i, y + i, w - 2*i, h - 2*i, color);
    }
}