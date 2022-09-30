#include "NavScreen.h"


NavScreen::NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames, Screen* navLeft, Screen* navRight, Screen* navSelect):
ImageScreen(frame_data, frame_len, frames), navLeft(navLeft), navRight(navRight), navSelect(navSelect) 
{
}

void NavScreen::nextFrame(void)
{
    frame += 1;
    if (frame == frames){
        frame = 0;
    }
    render();
}

void NavScreen::onLeft(void)
{
    Nav::gotoScreen(navLeft);
    _loaded = false;
}

void NavScreen::onRight(void)
{
    Nav::gotoScreen(navRight);
    _loaded = false;
}

void NavScreen::onSelect(void)
{
    Nav::gotoScreen(navSelect);
    _loaded = false;
}
