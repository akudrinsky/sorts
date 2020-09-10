#include "../include/statsInt.hpp"
#include "../include/compare.hpp"

#include "cstdio"
#include "cstring"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("You should set one or more options:\n\t\"sortAll\" for making comparings / swaps data from file ./data/tests.txt\n\t\"show\" for showing the results\n");
    }
    else if (argc == 2) {
        if (strncmp(argv[1], "sortAll", 7) == 0) {
            genData();
        }
        else if (strncmp(argv[1], "show", 4) == 0) {
            // TODO
        }
    }
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