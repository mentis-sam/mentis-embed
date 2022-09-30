#include "InputScreen.h"

InputScreen::InputScreen(const uint8_t* frame_data, const uint32_t* frame_len, uint8_t* var, const uint8_t range):
ImageScreen(frame_data, frame_len), _range(range), _var(var)
{
}


// Can only be called once 
void InputScreen::load(void)
{
    if (_loaded){
        return;
    }
    _frame = *_var;
    _loaded = true;
    render();
}

void InputScreen::nextFrame(void)
{
}

void InputScreen::onLeft(void)
{
    _rotate(0);
}

void InputScreen::onRight(void)
{
    _rotate(1);
}

void InputScreen::onSelect(void)
{
    Nav::gotoScreen(&Nav::settings_menu);
    _loaded = false;
}

void InputScreen::_rotate(bool inc)
{
    if (inc) {
        if (*_var == _range){
            *_var = 0;
        }else{
            *_var = *_var + 1; 
        }
    }else{
        if (*_var == 0){
            *_var = _range;
        }else{
            *_var = *_var - 1; 
        }
    }
    _frame = *_var;
    render();
}