#include "EventLog.h"
#include <iostream>
#include <stdexcept>

EventLog::EventLog(int initialCapacity) {
    if (initialCapacity < 1) {
        initialCapacity = 1;
    }
    capacity_ = initialCapacity;
    size_ = 0;
    events = new Event[capacity_];
}

EventLog::~EventLog() {
    delete[] events;
}

int EventLog::size() const {
    return size_;
}

int EventLog::capacity() const {
    return capacity_;
}

void EventLog::resize() {
    int newCapacity = capacity_ * 2;
    Event* newEvents = new Event[newCapacity];

    for (int i = 0; i < size_; i++) {
        newEvents[i] = events[i];
    }
    delete[] events;
    events = newEvents;
    capacity_ = newCapacity;
}

void EventLog::append(const Event& e) {
    if (size_ >= capacity_) {
        resize();
    }
    events[size_] = e;
    size_++;
}

Event EventLog::get(int index) const {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return events[index];
}
void EventLog::set(int index, const Event& e) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    events[index] = e;
}

bool EventLog::isEmpty() const {
    return size_ == 0;
}

void EventLog::print() const {
    if (isEmpty()) {
        std::cout << "Logg is empty" << std::endl;
        return;
    }
    std::cout << "\n=== Event Log (" << size_ << " events) ===" << std::endl;
    for (int i = 0; i < size_; i++) {
        printEvent(events[i]);
    }
    std::cout << "==========================\n" << std::endl;
}

bool EventLog::isSortedByTimestamp() const {
    for (int i = 0; i < size_ - 1; i++) {
        if (events[i].timestamp > events[i + 1].timestamp) {
            return false;
        }
    }
    return true;
}
void EventLog::shuffle() {
    if (size_ <= 1) {
        return;
    }
    // Fisher-Yates shuffle algorithm
    for (int i = size_ - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Event temp = events[i];
        events[i] = events[j];
        events[j] = temp;
    }

    std::cout << "Logg is now shuffled " << std::endl;
}