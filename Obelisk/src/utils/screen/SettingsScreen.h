#ifndef SETTINGS_SCREEN
#define SETTINGS_SCREEN

#include "utils/screen/ImageScreen.h"
#include "utils/NavManager.h"

class SettingsScreen: public ImageScreen {
public: 
    SettingsScreen(const uint8_t* frame_data, const uint32_t* frame_len);

    void load(void);
    void nextFrame(void);
    
    void render(void);
    void onSelect(void);
    void onLeft(void);
    void onRight(void);
private:
    void callFunc(int8_t id);
};


#endif /* SETTINGS_SCREEN */
