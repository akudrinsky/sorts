#include "../include/statsInt.hpp"
#include <cstdio>

#define GENERATE_COMPARE_OPERATOR_STATSINT(op)\
bool StatsInt::operator op (const StatsInt& other) {\
    ++compareNum;\
    return number op other.number;\
}

unsigned long StatsInt::compareNum = 0;
unsigned long StatsInt::swapNum = 0;

StatsInt::StatsInt(): number(0) {}
StatsInt::StatsInt(int number): number(number) {}
StatsInt::StatsInt(const StatsInt& other): number(other.number) {}

StatsInt& StatsInt::operator = (const StatsInt& other) {
    number = other.number;
    return *this;
}

StatsInt::operator int() {
    return number;
}

unsigned long StatsInt::showCompares() {
    return StatsInt::compareNum;
}

unsigned long StatsInt::showSwaps() {
    return StatsInt::swapNum;
}

void StatsInt::restart() {
    StatsInt::compareNum = 0;
    StatsInt::swapNum = 0;
}

GENERATE_COMPARE_OPERATOR_STATSINT(<)
GENERATE_COMPARE_OPERATOR_STATSINT(==)
GENERATE_COMPARE_OPERATOR_STATSINT(!=)
GENERATE_COMPARE_OPERATOR_STATSINT(>)
GENERATE_COMPARE_OPERATOR_STATSINT(<=)
GENERATE_COMPARE_OPERATOR_STATSINT(>=)

void std::swap(StatsInt& first, StatsInt& second) {
    //printf("SWAP: %d and %d\n", first.number, second.number);
    ++StatsInt::swapNum;
    int tmp = first.number;
    first.number = second.number;
    second.number = tmp;
}