#include "TftScreen.h"

TftScreen::TftScreen(char *title, TftScreen *parent)
{
    strcpy(this->title, title);
    this->parent = parent;
}