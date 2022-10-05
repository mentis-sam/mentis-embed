#include "CancelScreen.h"

CancelScreen::CancelScreen(const uint8_t* frame_data, const uint32_t* frame_len, Screen* fromScreen, Screen* returnScreen, void (*cancelCallback)()):
ImageScreen(frame_data, frame_len), _state(false), _fromScreen(fromScreen), _returnScreen(returnScreen), _cancelCallback(cancelCallback)
{
}

void CancelScreen::nextFrame(void)
{
}

void CancelScreen::onLeft(void)
{
    if (_frame == 0){
        _frame = 1;
        render();
    }
}

void CancelScreen::onRight(void)
{
    if (_frame == 1){
        _frame = 0;
        render();
    }
}

void CancelScreen::onSelect(void)
{
    if (_frame == 0){
        Nav::gotoScreen(_fromScreen);
        _loaded = false;
    }else{
        _cancelCallback();
        Nav::gotoScreen(_returnScreen);
        _loaded = false;
    }
    
}