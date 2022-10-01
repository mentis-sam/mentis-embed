#include "SettingsScreen.h"

const int8_t nav_screens = 17;

enum s {
    s_1, s_2, s_3, s_4,
    c_1, c_2, c_3, c_4,
    f_1, f_2, f_3, f_4, f_5,
    b_1, b_2, b_3, b_4
};

enum f {
    f_bk = -128,
    fc_1 = -1,
    fc_2 = -2,
    fc_3 = -3,
    ff_1 = -4,
    ff_2 = -5,
    ff_3 = -6,
    ff_4 = -7,
    fb_1 = -8,
    fb_2 = -9,
    fb_3 = -10
};

// Negative numbers denote functions (pretty hacky)
// deffo replace with an enum
const int8_t nav_lookup[nav_screens*3] = {
    s_4, s_1, s_2, s_3, c_4, c_1, c_2, c_3, f_5, f_1, f_2, f_3, f_4, b_4, b_1, b_2, b_3,           //Left
    s_2, s_3, s_4, s_1, c_2, c_3, c_4, c_1, f_2, f_3, f_4, f_5, f_1, b_2, b_3, b_4, b_1,           //Right
    c_1, f_1, b_1, f_bk, fc_1, fc_2, fc_3, s_1, ff_1, ff_2, ff_3, ff_4, s_2, fb_1, fb_2, fb_3, s_3 //Select
};

SettingsScreen::SettingsScreen(const uint8_t* frame_data, const uint32_t* frame_len):
ImageScreen(frame_data, frame_len) 
{
}

void SettingsScreen::load(void){
    if (_loaded){
        return;
    }
    _loaded = true;
    render();
}

void SettingsScreen::nextFrame(void)
{
}

void SettingsScreen::onLeft(void)
{
    if (nav_lookup[_frame] < 0){
        callFunc(nav_lookup[_frame]);
    }else{
        _frame = nav_lookup[_frame];
        render();
    }
}

void SettingsScreen::onRight(void)
{
    if (nav_lookup[_frame+nav_screens] < 0){
        callFunc(nav_lookup[_frame+nav_screens]);
    }else{
        _frame = nav_lookup[_frame+nav_screens];
        render();
    }
}

void SettingsScreen::onSelect(void)
{
    if (nav_lookup[_frame+nav_screens*2] < 0){
        callFunc(nav_lookup[_frame+nav_screens*2]);
    }else{
        _frame = nav_lookup[_frame+nav_screens*2];
        render();
    }
}

void SettingsScreen::callFunc(int8_t id){
    switch (id)
    {
    case f_bk:
        Nav::gotoScreen(&Nav::menu_settings);
        _frame = 0;
        _loaded = false;
        break;
    case fc_1:
        Nav::gotoScreen(&Nav::settings_c_time);
        _loaded = false;
        break;
    case fc_2:
        Nav::gotoScreen(&Nav::settings_c_temp);
        _loaded = false;
        break;
    case fc_3:
        Nav::gotoScreen(&Nav::settings_c_airflow);
        _loaded = false;
        break;
    case ff_1:
        Nav::gotoScreen(&Nav::settings_f_time);
        _loaded = false;
        break;
    case ff_2:
        Nav::gotoScreen(&Nav::settings_f_temp);
        _loaded = false;
        break;
    case ff_3:
        Nav::gotoScreen(&Nav::settings_f_airflow);
        _loaded = false;
        break;
    case ff_4:
        Nav::gotoScreen(&Nav::settings_f_light);
        _loaded = false;
        break;
    case fb_1:
            
        break;
    case fb_2:
            
        break;
    case fb_3:
            
        break;
    default:
        return;
    }
}