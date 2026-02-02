#ifndef SORTSTRATEGY_H
#define SORTSTRATEGY_H

#include "EventLog.h"
#include <string>

typedef void (*SortFunction)(EventLog* log);
void insertionSort(EventLog* log);
void selectionSort(EventLog* log);
class SortStrategy {
public:
    static SortFunction getSortFunction(const std::string& name);
    static void listAvailableSorts();
};

#endif 