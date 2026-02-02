#ifndef ALARMSET_H
#define ALARMSET_H

class AlarmSet {
private:
    int* sensorIds;
    int count;
    int capacity_;
    int threshold;

    int findIndex(int sensorId) const;

public:
    AlarmSet(int initialCapacity = 10);

    ~AlarmSet();

    void add(int sensorId);

    void remove(int sensorId);

    bool contains(int sensorId) const;

    void printAlarms() const;

    int size() const;

    void setThreshold(int value);

    int getThreshold() const;
};

#endif