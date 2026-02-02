#include "EventQueue.h"

EventQueue::EventQueue(int capacity) {
    if (capacity < 1) {
        capacity = 1;
    }
    capacity_ = capacity;
    buffer = new Event[capacity_];
    head = 0;
    tail = 0;
    count = 0;
}

EventQueue::~EventQueue() {
    delete[] buffer;
}

bool EventQueue::isEmpty() const {
    return count == 0;
}

bool EventQueue::isFull() const {
    return count == capacity_;
}

bool EventQueue::enqueue(const Event& e) {
    if (isFull()) {
        return false;
    }

    buffer[tail] = e;
    tail = (tail + 1) % capacity_;
    count++;
    return true;
}

bool EventQueue::dequeue(Event& out) {
    if (isEmpty()) {
        return false;
    }

    out = buffer[head];
    head = (head + 1) % capacity_;
    count--;

    return true;
}

int EventQueue::size() const {
    return count;
}

int EventQueue::capacity() const {
    return capacity_;
}