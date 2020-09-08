#include "../include/statsInt.hpp"
#include "../include/compare.hpp"

#include "cstdio"

int main() {
    int size = 10;
    StatsInt* data = new StatsInt[size];
    for (int i = 0; i < size; ++i) {
        data[i] = size - i;
    }

    bubbleSort(data, size);
    printf("Comparisons: %lu, swaps: %lu\n", StatsInt::showCompares(), StatsInt::showSwaps());

    StatsInt::restart();

    delete [] data;
}