#pragma once

#include "../include/statsInt.hpp"
#include "usefulDefines.hpp"

#include "algorithm"
#include "vector"
#include "unordered_map"

/*
Generates statistics for swaps and compares for all emplemented sorting algorithms
*/
void GenStats();

/*
Compares 
*/
class comparator {
public:
    // Constructor.
    // testDataName - name of a test data file (with raw data)
    // resultDataName - name of a result data with ready statistics
    comparator(const char* testDataName, const char* resultDataName, void (*algorithm)(StatsInt* data, int size));

    NON_COPYBLE(comparator)

    ~comparator();

    // Makes statistics from a given file by a given algo
    void makeStats();
    // Makes statistics from a file to a file
    bool getLineStats();

private:
    FILE* testData;
    FILE* resultData;

    std::unordered_map<int, std::vector<int>> comparings;
    std::unordered_map<int, std::vector<int>> swaps;

    void (*algorithm)(StatsInt* data, int size);

    bool fillArray(StatsInt* data, int arraySize);
};

template<typename T>
T mean(std::vector<T>& data) {
    if (data.empty()) {
        LOGS("INFO >>> empty vector in mean function\n")
        return T();
    }
    T sum = 0;
    for (auto elem = data.begin(); elem != data.end(); ++elem) {
        sum += *elem;
    }
    return sum / data.size();
}

template<typename T>
void BubbleSort(T* data, int size) {
    int preSize = size - 1;
    for (int i = 0; i < preSize; ++i) {
        for (int j = i; j < size; ++j) {
            if (data[i] > data[j]) {
                std::swap(data[i], data[j]);
            }
        }
    }
}

template<typename T>
void QuickSort(T* data, int size) {
    //LOGS("INFO >>> QSORT!!!!!!!\n")
    innerQuickSort(data, 0, size);
}

template<typename T>
void innerQuickSort(T* data, int low, int high) {
    int i = low;
    int j = high;
    T pivot = data[(i + j) / 2];

    while (i <= j) {
        while (data[i] < pivot) {
            i++;
        }
        while (data[j] > pivot) {
            j--;
        }
        if (i <= j) {
            std::swap(data[i], data[j]);
            LOGS("INFO >>> swap %d <-> %d\n", int(data[i]), int(data[j]))
            i++;
            j--;
        }
    }

    if (j > low) {
        innerQuickSort(data, low, j);
    }
    if (i < high) {
        innerQuickSort(data, i, high);
    }
}