#pragma once

#include <vector>
#include "usefulDefines.hpp"

class StatsInt;

namespace std {
    void swap(StatsInt& first, StatsInt& second);
}
struct Stats {
    Stats(const char* filename);

    NON_COPYBLE(Stats);

    std::vector<int> sizes;
    std::vector<int> swaps;
    std::vector<int> compares;
};

class StatsInt {
public:
    StatsInt();
    StatsInt(int number);
    StatsInt(const StatsInt& other);
    StatsInt& operator = (const StatsInt& other);

    operator int();

    static unsigned long showCompares();
    static unsigned long showSwaps();

    static void restart();

    bool operator < (const StatsInt& other);
    bool operator == (const StatsInt& other);
    bool operator != (const StatsInt& other);
    bool operator > (const StatsInt& other);
    bool operator <= (const StatsInt& other);
    bool operator >= (const StatsInt& other);

private:
    int number;
    static unsigned long compareNum;
    static unsigned long swapNum;
    
    friend void std::swap(StatsInt& first, StatsInt& second);
};