#include "../include/statsInt.hpp"
#include "../include/compare.hpp"
#include "../include/sortsApp.hpp"
#include "../include/makeApp.hpp"

#include "cstdio"
#include "cstring"

namespace {
    void checkArg(char* arg);
};

int main(int argc, char *argv[]) {
    switch (argc) {
    case 1:
        printf("You should set one or more options:\n\t\"sortAll\" for making comparings / swaps data from file ./data/tests.txt\n\t\"show\" for showing the results\n");
        break;
    case 2:
        checkArg(argv[1]);
        break;
    case 3:
        checkArg(argv[1]);
        checkArg(argv[2]);
        break;
    default:
        printf("ERROR >>> two many (%d) command line arguments\n", argc);
        break;
    }
}

namespace {
    void checkArg(char* arg) {
        if (strncmp(arg, "sortAll", 7) == 0) {
            GenStats();
        }
        else if (strncmp(arg, "show", 4) == 0) {
            MakeApp();
        }
    }
}