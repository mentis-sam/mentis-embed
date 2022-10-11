#include "NavScreen.h"


NavScreen::NavScreen(const uint8_t* frame_data, const uint32_t* frame_len, const uint8_t frames, Screen* navLeft, Screen* navRight, Screen* navSelect, void (*loadCallback)(), void (*renderCallback)()):
ImageScreen(frame_data, frame_len), _frames(frames), _navLeft(navLeft), _navRight(navRight), _navSelect(navSelect), _loadCallback(loadCallback), _renderCallback(renderCallback)
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

void NavScreen::render(void){
    ImageScreen::render();
    _renderCallback();
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
}

void NavScreen::onRight(void)
{
    Nav::gotoScreen(_navRight, false);
}

void NavScreen::onSelect(void)
{
    Nav::gotoScreen(_navSelect, false);
}
