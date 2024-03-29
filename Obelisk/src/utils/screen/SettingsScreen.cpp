#include "SettingsScreen.h"

const int8_t nav_screens = 25;

enum s {
    s_1, s_2, s_3, s_4, s_5, s_6,
    c_1, c_2, c_3, c_4,
    f_1, f_2, f_3, f_4, f_5,
    d_1, d_2, d_3,
    b_1, b_2, b_3, b_4, b_5,
    r_1, r_2
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
    fd_1 = -8,
    fd_2 = -9,
    fb_1 = -10,
    fb_2 = -11,
    fb_3 = -12,
    fb_4 = -13,
    fr_1 = -14
};

// Negative numbers denote functions (pretty hacky)
// deffo replace with an enum
const int8_t nav_lookup[nav_screens*3] = {
    s_6, s_1, s_2, s_3, s_4, s_5, c_4, c_1, c_2, c_3, f_5, f_1, f_2, f_3, f_4, d_3, d_1, d_2, b_5, b_1, b_2, b_3, b_4, r_2, r_1,  //Left
    s_2, s_3, s_4, s_5, s_6, s_1, c_2, c_3, c_4, c_1, f_2, f_3, f_4, f_5, f_1, d_2, d_3, d_1, b_2, b_3, b_4, b_5, b_1, r_2, r_1,   //Right
    c_1, f_1, d_1, b_1, r_1, f_bk, fc_1, fc_2, fc_3, s_1, ff_1, ff_2, ff_3, ff_4, s_2, fd_1, fd_2, s_3, fb_1, fb_2, fb_3, fb_4, s_4, fr_1, s_5 //Select
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

void SettingsScreen::render(void)
{
    ImageScreen::render();
    if (_frame == s_4 || _frame == b_1 || _frame == b_2 || _frame == b_3 || _frame == b_4 || _frame == b_5){
        uint8_t ypos = 34; 

        switch(Settings::settings.beep){
            case on_harvest:
                ypos = 34;
                break;
            case on_drying:
                ypos = 66;
                break;
            case both:
                ypos = 90;
                break;
            case never:
                ypos = 114;
                break;
        };
        tft.fillCircle(305, ypos, 3, TFT_DARKGREY);
    }
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
        Settings::saveSettings();
        _frame = 0;
        break;
    case fc_1:
        Nav::gotoScreen(&Nav::settings_c_time);
        break;
    case fc_2:
        Nav::gotoScreen(&Nav::settings_c_temp);
        break;
    case fc_3:
        Nav::gotoScreen(&Nav::settings_c_airflow);
        break;
    case ff_1:
        Nav::gotoScreen(&Nav::settings_f_time);
        break;
    case ff_2:
        Nav::gotoScreen(&Nav::settings_f_temp);
        break;
    case ff_3:
        Nav::gotoScreen(&Nav::settings_f_airflow);
        break;
    case ff_4:
        Nav::gotoScreen(&Nav::settings_f_light);
        break;
    case fd_1:
        Nav::gotoScreen(&Nav::settings_d_time);
        break;
    case fd_2:
        Nav::gotoScreen(&Nav::settings_d_temp);
        break;
    case fb_1:
        Settings::settings.beep = on_harvest;
        render();
        break;
    case fb_2:
        Settings::settings.beep = on_drying;
        render();
        break;
    case fb_3:
        Settings::settings.beep = both;
        render();
        break;
    case fb_4:
        Settings::settings.beep = never;
        render();
        break;
    case fr_1:
        Nav::gotoScreen(&Nav::settings_factory_rs);
        break;
    default:
        return;
    }
}