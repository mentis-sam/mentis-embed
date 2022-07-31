#ifndef SCREEN_UTILS_H
#define SCREEN_UTILS_H

#include "TFT_eSPI.h"
extern TFT_eSPI tft;

void drawRectStroke(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t stroke, uint32_t color);

#endif /* SCREEN_UTILS */
