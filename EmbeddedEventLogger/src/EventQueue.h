#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "Event.h"

class EventQueue {
private:
    Event* buffer;
    int capacity_;
    int head;
    int tail;
    int count;

public:
    EventQueue(int capacity);

    ~EventQueue();

    bool isEmpty() const;
    bool isFull() const;
    bool enqueue(const Event& e);
    bool dequeue(Event& out);
    int size() const;
    int capacity() const;
};

#endif