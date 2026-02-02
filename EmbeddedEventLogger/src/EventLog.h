#ifndef EVENTLOG_H
#define EVENTLOG_H

#include "Event.h"

class EventLog {
private:
    Event* events;
    int size_;
    int capacity_;
    void resize();

public:
    EventLog(int initialCapacity = 10);

    ~EventLog();

    int size() const;
    int capacity() const;
    void append(const Event& e);
    Event get(int index) const;
    void set(int index, const Event& e);
    void print() const;
    bool isEmpty() const;
    bool isSortedByTimestamp() const;
    void shuffle();         // shuffles the order of events (to test the sorting algorithm)
};

#endif