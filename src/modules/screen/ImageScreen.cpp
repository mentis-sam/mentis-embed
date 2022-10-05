#include "ImageScreen.h"

PNG png; // PNG decoder inatance

ImageScreen::ImageScreen(const uint8_t* frame_data, const uint32_t* frame_len):
Screen(), _frame_d(frame_data), _frame_l(frame_len)
{
}

// TODO: Render screen in one - might be faster
void ImageScreen::_pngDraw(PNGDRAW *pDraw) {
  uint16_t lineBuffer[SCREEN_WIDTH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, -1);
  Screen::tft.pushImage(0, pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

// Can only be called once 
void ImageScreen::load(void)
{
    if (_loaded){
        return;
    }
    _frame = 0;
    _loaded = true;
    render();
}

void ImageScreen::render(void)
{
    // Dont render if not loaded
    if (!_loaded){
        return;
    }

    // TODO: This could be faster if precalced
    int offset = 0;
    for (int i = 0; i < _frame; i++){
        offset += _frame_l[i];
    };

    int16_t rc = png.openFLASH((uint8_t*)&_frame_d[offset], _frame_l[_frame], _pngDraw);
    if (rc == PNG_SUCCESS) {
        rc = png.decode(NULL, 0);
        png.close();
    };

    tft.drawString("Hello", SCREEN_WIDTH/2, 30); 
}
