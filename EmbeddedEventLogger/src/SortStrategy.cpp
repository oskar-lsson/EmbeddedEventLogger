#include "SortStrategy.h"
#include <iostream>
#include <algorithm>

void insertionSort(EventLog* log) {
    int n = log->size();
    if (n <= 1) {
        return;
    }
    for (int i = 1; i < n; i++) {
        Event key = log->get(i);
        int j = i - 1;

        while (j >= 0 && log->get(j).timestamp > key.timestamp) {
            log->set(j + 1, log->get(j));
            j--;
        }
        log->set(j + 1, key);
    }
    std::cout << "Sorted with Insertion Sort" << std::endl;
}

void selectionSort(EventLog* log) {
    int n = log->size();

    if (n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (log->get(j).timestamp < log->get(minIndex).timestamp) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            Event temp = log->get(i);
            log->set(i, log->get(minIndex));
            log->set(minIndex, temp);
        }
    }

    std::cout << "Sorted with Selection Sort" << std::endl;
}

SortFunction SortStrategy::getSortFunction(const std::string& name) {
    if (name == "insertion") {
        return insertionSort;
    }
    else if (name == "selection") {
        return selectionSort;
    }
    else {
        return nullptr;
    }
}

// Listar tillgängliga sorteringsalgoritmer
void SortStrategy::listAvailableSorts() {
    std::cout << "Available sorting algorithms:" << std::endl;
    std::cout << "  - insertion  (Insertion Sort)" << std::endl;
    std::cout << "  - selection  (Selection Sort)" << std::endl;
}