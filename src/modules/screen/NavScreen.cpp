#include "NavScreen.h"


NavScreen::NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames, Screen* navLeft, Screen* navRight, Screen* navSelect, void (*loadCallback)()):
ImageScreen(frame_data, frame_len), _frames(frames), _navLeft(navLeft), _navRight(navRight), _navSelect(navSelect), _loadCallback(loadCallback)
{
}

// Can only be called once 
void NavScreen::load(void)
{
    if (_loaded){
        return;
    }
    _frame = 0;
    _loaded = true;
    _loadCallback();
    render();
}

void NavScreen::nextFrame(void)
{
    _frame += 1;
    if (_frame == _frames){
        _frame = 0;
    }
    render();
}

void NavScreen::onLeft(void)
{
    Nav::gotoScreen(_navLeft, false);
    _loaded = false;
}

void NavScreen::onRight(void)
{
    Nav::gotoScreen(_navRight, false);
    _loaded = false;
}

void NavScreen::onSelect(void)
{
    Nav::gotoScreen(_navSelect, false);
    _loaded = false;
}
