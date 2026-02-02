#ifndef EVENT_H
#define EVENT_H

enum EventType {
    TEMP,
    BUTTON,
    MOTION
};


struct Event {
    int timestamp;
    int sensorId;
    EventType type;
    int value;
};

Event createEvent(int sensorId, EventType type, int value);
void printEvent(const Event& e);
const char* eventTypeToString(EventType type);

#endif