#ifndef TFTMENUSCREEN
#define TFTMENUSCREEN

#include <TFT_eSPI.h>
#include "TftScreen.h"

extern TFT_eSPI tft;
extern TftScreen *currentScreen;
extern volatile int8_t g_rotValue;

// class TftMenuItem {
// public:
//     TftMenuItem(char *name);
//     char name[255];
//     TftScreen *next;
// };

typedef struct {
    char name[255];
    TftScreen *next;
} TftMenuItem;


class TftMenuScreen: TftScreen {
public:
    TftMenuItem choices[10]; 
    int highlightedItem;
    int nChoices;
    int window;

    TftMenuScreen(char *title, TftScreen *parent);
    void addItem(const char *name, TftScreen *next);

    // void setChoices(TftMenuItem **choices, int len);
    void rerender(void);
    void render(void);
    void onClick(void);
    void onRotation(void);
};


#endif /* TFTMENUSCREEN */
