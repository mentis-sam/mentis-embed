#ifndef NOTIFY_H
#define NOTIFY_H

#include "IO.h"
class Notify{
public:
    Notify();

    static void set_notification(void);

    static void update(void);

    static void clear_notification(void);
    static bool sleep;
private:
    static int  _screenTime;
    static bool _screenOn;
    static bool _notify;

};

#endif