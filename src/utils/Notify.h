#ifndef NOTIFY_H
#define NOTIFY_H

class Notify{
public:
    Notify();

    void set_notification(void);

    void update(void);
private:
    bool _notify;
};

#endif