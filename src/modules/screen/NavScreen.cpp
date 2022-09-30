#include "NavScreen.h"


NavScreen::NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames, Screen* navLeft, Screen* navRight, Screen* navSelect):
ImageScreen(frame_data, frame_len), frames(frames), navLeft(navLeft), navRight(navRight), navSelect(navSelect) 
{
}

void NavScreen::nextFrame(void)
{
    _frame += 1;
    if (_frame == frames){
        _frame = 0;
    }
    render();
}

void NavScreen::onLeft(void)
{
    Nav::gotoScreen(navLeft, false);
    _loaded = false;
}

void NavScreen::onRight(void)
{
    Nav::gotoScreen(navRight, false);
    _loaded = false;
}

void NavScreen::onSelect(void)
{
    Nav::gotoScreen(navSelect, false);
    _loaded = false;
}
