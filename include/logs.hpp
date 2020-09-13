#pragma once
//#define DEBUG

#ifdef DEBUG
    #define LOGS(...) printf(__VA_ARGS__);
#else
    #define LOGS(data, ...) ;
#endif