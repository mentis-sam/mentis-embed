#ifndef INPUT_SCREEN
#define INPUT_SCREEN

#include "modules/screen/ImageScreen.h"

#include "utils/NavManager.h"


class InputScreen: public ImageScreen {
public: 
    InputScreen(const uint8_t* frame_data, const uint32_t* frame_len, uint16_t* var, const uint8_t range);

    void load(void);
    void nextFrame(void);
    
    void onSelect(void);
    void onLeft(void);
    void onRight(void);
private:
    const uint8_t  _range;
    uint16_t*       _var;

    void _rotate(bool inc);
};


#endif /* INPUT_SCREEN */
