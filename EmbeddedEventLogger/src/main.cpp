#include "Event.h"
#include "EventLog.h"
#include "EventQueue.h"
#include "SortStrategy.h"
#include "AlarmSet.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

Event createRandomEvent() {
    int sensorId = rand() % 5 + 1;
    EventType type = (EventType)(rand() % 3);
    int value;

    switch (type) {
    case TEMP:
        value = rand() % 60 + 10;
        break;
    case BUTTON:
        value = rand() % 2;
        break;
    case MOTION:
        value = rand() % 100;
        break;
    }

    return createEvent(sensorId, type, value);
}

void updateAlarms(const Event& e, AlarmSet& alarms) {
    if (e.type == TEMP) {
        if (e.value > alarms.getThreshold()) {
            alarms.add(e.sensorId);
        }
        else {
            alarms.remove(e.sensorId);
        }
    }
}

void tick(int n, EventQueue& queue, EventLog& log, AlarmSet& alarms) {
    int produced = 0;
    int consumed = 0;

    for (int i = 0; i < n; i++) {
        Event newEvent = createRandomEvent();
        if (queue.enqueue(newEvent)) {
            produced++;
        }

        Event processedEvent;
        if (queue.dequeue(processedEvent)) {
            log.append(processedEvent);
            updateAlarms(processedEvent, alarms);
            consumed++;
        }
    }

    std::cout << "Tick run " << n << " iterations:" << std::endl;
    std::cout << "  Produced: " << produced << " events" << std::endl;
    std::cout << "  Consumed: " << consumed << " events" << std::endl;
    std::cout << "  Size of queue " << queue.size() << "/" << queue.capacity() << std::endl;
    std::cout << "  Size of logg: " << log.size() << std::endl;
}

void findBySensor(const EventLog& log, int sensorId) {
    std::cout << "\n=== Events for Sensor " << sensorId << " ===" << std::endl;
    int found = 0;

    for (int i = 0; i < log.size(); i++) {
        Event e = log.get(i);
        if (e.sensorId == sensorId) {
            printEvent(e);
            found++;
        }
    }

    if (found == 0) {
        std::cout << "No events was found for " << sensorId << std::endl;
    }
    else {
        std::cout << "Total " << found << " events was found" << std::endl;
    }
    std::cout << "==============================\n" << std::endl;
}

void showHelp() {
    std::cout << "\n=== Available Commands ===" << std::endl;
    std::cout << "  tick <n>           - Run n iterations off event loop" << std::endl;
    std::cout << "  print              - Print the logg" << std::endl;
    std::cout << "  shuffle            - Shuffles the loggs order (to test sorting algorithm" << std::endl;
    std::cout << "  sort <algoritm>    - Sort the logg (insertion/selection)" << std::endl;
    std::cout << "  find <sensorId>    - Finding all elements of a specific sensor" << std::endl;
    std::cout << "  alarms             - Show active alarm" << std::endl;
    std::cout << "  set-threshold <n>  - Set threshold for temperature" << std::endl;
    std::cout << "  status             - Show system status" << std::endl;
    std::cout << "  help               - Shows help list" << std::endl;
    std::cout << "  exit               - Exit the program" << std::endl;
    std::cout << "==============================\n" << std::endl;
}

// Visa systemstatus
void showStatus(const EventQueue& queue, const EventLog& log, const AlarmSet& alarms) {
    std::cout << "\n=== System status ===" << std::endl;
    std::cout << "Queue: " << queue.size() << "/" << queue.capacity() << " events" << std::endl;
    std::cout << "Logg: " << log.size() << " events" << std::endl;
    std::cout << "Active alarm: " << alarms.size() << std::endl;
    std::cout << "Alarm threshold: " << alarms.getThreshold() << "\370C" << std::endl;
    std::cout << "Logg sorted by timestamp: " << (log.isSortedByTimestamp() ? "Yes" : "No") << std::endl;
    std::cout << "====================\n" << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    EventQueue queue(10);
    EventLog log(20);
    AlarmSet alarms(10);

    std::cout << "==================================" << std::endl;
    std::cout << "  Embedded Event Logger System" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Write 'help' to see available commands.\n" << std::endl;

    std::string line;
    bool running = true;

    while (running) {
        std::cout << "> ";
        std::getline(std::cin, line);

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "exit") {
            running = false;
            std::cout << " Exits the program " << std::endl;
        }
        else if (command == "help") {
            showHelp();
        }
        else if (command == "tick") {
            int n;
            if (iss >> n && n > 0) {
                tick(n, queue, log, alarms);
            }
            else {
                std::cout << "Use: tick <n> where n > 0" << std::endl;
            }
        }
        else if (command == "print") {
            log.print();
        }
        else if (command == "shuffle") {
            log.shuffle();
            std::cout << "Logg is now sorted: "
                << (log.isSortedByTimestamp() ? "Yes" : "No") << std::endl;
        }
        else if (command == "sort") {
            std::string sortName;
            if (iss >> sortName) {
                SortFunction sortFunc = SortStrategy::getSortFunction(sortName);
                if (sortFunc != nullptr) {
                    sortFunc(&log);
                    std::cout << "Logg is now sorted: "
                        << (log.isSortedByTimestamp() ? "Yes" : "No") << std::endl;
                }
                else {
                    std::cout << "Unknown sorting algorithm: " << sortName << std::endl;
                    SortStrategy::listAvailableSorts();
                }
            }
            else {
                std::cout << "Use: sort <algoritm>" << std::endl;
                SortStrategy::listAvailableSorts();
            }
        }
        else if (command == "find") {
            int sensorId;
            if (iss >> sensorId) {
                findBySensor(log, sensorId);
            }
            else {
                std::cout << "Use: find <sensorId>" << std::endl;
            }
        }
        else if (command == "alarms") {
            alarms.printAlarms();

        }
        else if (command == "set-threshold") {
            int threshold;
            if (iss >> threshold) {
                alarms.setThreshold(threshold);
            }
            else {
                std::cout << "Use: set-threshold <value>" << std::endl;
            }
        }
        else if (command == "status") {
            showStatus(queue, log, alarms);
        }
        else if (command.empty()) {
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
            std::cout << "Write 'help' to see available commands." << std::endl;
        }
    }
    return 0;
}