#include "AlarmSet.h"
#include <iostream>

AlarmSet::AlarmSet(int initialCapacity) {
    if (initialCapacity < 1) {
        initialCapacity = 1;
    }
    capacity_ = initialCapacity;
    count = 0;
    threshold = 30;
    sensorIds = new int[capacity_];
}


AlarmSet::~AlarmSet() {
    delete[] sensorIds;
}

int AlarmSet::findIndex(int sensorId) const {
    for (int i = 0; i < count; i++) {
        if (sensorIds[i] == sensorId) {
            return i;
        }
    }
    return -1;
}

void AlarmSet::add(int sensorId) {
    if (contains(sensorId)) {
        return;
    }

    if (count >= capacity_) {
        int newCapacity = capacity_ * 2;
        int* newArray = new int[newCapacity];

        for (int i = 0; i < count; i++) {
            newArray[i] = sensorIds[i];
        }

        delete[] sensorIds;
        sensorIds = newArray;
        capacity_ = newCapacity;
    }

    sensorIds[count] = sensorId;
    count++;

    std::cout << " ALARM: Sensor " << sensorId << " activated!" << std::endl;
}

void AlarmSet::remove(int sensorId) {
    int index = findIndex(sensorId);

    if (index == -1) {
        return;
    }

    sensorIds[index] = sensorIds[count - 1];
    count--;

    std::cout << " Sensor " << sensorId << " alarm deactivated." << std::endl;
}

bool AlarmSet::contains(int sensorId) const {
    return findIndex(sensorId) != -1;
}

void AlarmSet::printAlarms() const {
    if (count == 0) {
        std::cout << "No active alarms." << std::endl;
        return;
    }

    std::cout << "\n=== Active Alarms (" << count << ") ===" << std::endl;
    std::cout << "Threshold: " << threshold << "°C" << std::endl;
    for (int i = 0; i < count; i++) {
        std::cout << " Sensor " << sensorIds[i] << std::endl;
    }
    std::cout << "========================\n" << std::endl;
}

int AlarmSet::size() const {
    return count;
}

void AlarmSet::setThreshold(int value) {
    threshold = value;
    std::cout << "Threshold is set at: " << threshold << "°C" << std::endl;
}

int AlarmSet::getThreshold() const {
    return threshold;
}