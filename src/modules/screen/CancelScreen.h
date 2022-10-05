#ifndef CANCEL_SCREEN_H
#define CANCEL_SCREEN_H

#include "modules/screen/ImageScreen.h"

#include "utils/NavManager.h"


class CancelScreen: public ImageScreen {
public: 
    CancelScreen(const uint8_t* frame_data, const uint32_t* frame_len, Screen* fromScreen, Screen* returnScreen, void (*loadCallback)());

    void nextFrame(void);
    
    void onSelect(void);
    void onLeft(void);
    void onRight(void);
private:
    void      (*_cancelCallback)();
    Screen*   _fromScreen;
    Screen*   _returnScreen;
    bool      _state;
};


#endif /* CANCEL_SCREEN_H */
