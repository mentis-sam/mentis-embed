#include "ImageScreen.h"

PNG png; // PNG decoder inatance

ImageScreen::ImageScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames):
Screen(), frame_d(frame_data), frame_l(frame_len), frames(frames)
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
    frame = 0;
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
    for (int i = 0; i < frame; i++){
        offset += frame_l[i];
    };

    int16_t rc = png.openFLASH((uint8_t*)&frame_d[offset], frame_l[frame], _pngDraw);
    if (rc == PNG_SUCCESS) {
        rc = png.decode(NULL, 0);
        png.close();
    };
}
