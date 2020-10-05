#include "../settings/settings.hpp"

#include "../include/compare.hpp"
#include "../include/usefulDefines.hpp"

#include "cstdio"
#include "cstring"
#include "vector"

void GenStats() {
    LOGS("INFO >>> Bubble sort\n")
    comparator bubble (settings::testData, settings::bubbleData, BubbleSort);
    bubble.makeStats();

    LOGS("INFO >>> Quick sort\n")
    comparator quick (settings::testData, settings::quickData, QuickSort);
    quick.makeStats();
}

comparator::comparator(const char* testDataName, const char* resultDataName, void (*algorithm)(StatsInt* data, int size)): 
        testData(fopen(testDataName, "r")), 
        resultData(fopen(resultDataName, "w")),
        algorithm(algorithm) {
    LOGS("INFO >>> opening files to make statistics of sorting algorithms\n");
    if (testData == nullptr) {            
        printf("ERROR >>> couldn't open file %s\n", testDataName);
    }
    if (resultData == nullptr) {
        printf("ERROR >>> couldn't open file %s\n", resultDataName);
    }
}

comparator::~comparator() {
    fclose(testData);
    fclose(resultData);
    LOGS("INFO >>> closed files with statistics of sorting algorithms\n");
}

bool comparator::getLineStats() {
    StatsInt* data = new StatsInt[settings::maxLength];
    // defer(delete [] data;);
    // defer(StatsInt::restart(););

    int arraySize = -1;
    if (fscanf(testData, "%d:", &arraySize) != 1) {
        return true;
    }

    if (fillArray(data, arraySize) == false) {
        return true;
    }    

    (*algorithm)(data, arraySize);

    //fprintf(resultData, "%d: %lu %lu\n", arraySize, StatsInt::showCompares(), StatsInt::showSwaps());
    comparings[arraySize].push_back(StatsInt::showCompares());
    swaps[arraySize].push_back(StatsInt::showSwaps());
    //LOGS("INFO >>> Comparisons: %lu, swaps: %lu\n", StatsInt::showCompares(), StatsInt::showSwaps());

    delete [] data;
    StatsInt::restart();

    return false;
}

void comparator::makeStats() {
    while (getLineStats() == false) {}

    for (auto lineCompare = comparings.begin(), lineSwap = swaps.begin();
            lineCompare != comparings.end() and lineSwap != swaps.end();
            ++lineCompare, ++lineSwap) {
        if (lineCompare->first != lineSwap->first) {
            printf("ERROR >>> different sizes of the same array in compares and swaps\n");
        }
        const int arrSize = lineCompare->first;
        const int meanCompares = mean(lineCompare->second);
        const int meanSwaps = mean(lineSwap->second);

        fprintf(resultData, "%i: %i %i\n", arrSize, meanCompares, meanSwaps);
    }

    LOGS("INFO >>> stats were made\n")
}

bool comparator::fillArray(StatsInt* data, int arraySize) {
    if (arraySize < 0) {
        LOGS("ERROR >> found negative sized array while making stats\n")
        return false;
    }
    int x = -1;
    for (int i = 0; i < arraySize; ++i) {
        fscanf(testData, " %d", &x);
        data[i] = x;
        //LOGS("INFO >>> found %d in a file\n", x)
    }

    fgetc(testData);
    return true;
}