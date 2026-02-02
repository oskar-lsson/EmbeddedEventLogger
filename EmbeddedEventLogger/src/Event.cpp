#include "Event.h"
#include <iostream>

static int globalTimestamp = 0;

Event createEvent(int sensorId, EventType type, int value) {
    Event e;
    e.timestamp = globalTimestamp++;
    e.sensorId = sensorId;
    e.type = type;
    e.value = value;
    return e;
}

const char* eventTypeToString(EventType type) {
    switch (type) {
    case TEMP: return "TEMP";
    case BUTTON: return "BUTTON";
    case MOTION: return "MOTION";
    default: return "UNKNOWN";
    }
}

void printEvent(const Event& e) {
    std::cout << "[" << e.timestamp << "] "
        << "Sensor " << e.sensorId << " - "
        << eventTypeToString(e.type) << ": "
        << e.value << std::endl;
}