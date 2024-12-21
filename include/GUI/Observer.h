#ifndef OBSERVER_H
#define OBSERVER_H

class Event;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify(const Event *event) = 0;
};


#endif // OBSERVER_H