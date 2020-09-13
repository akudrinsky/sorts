#pragma once

#include "../settings/settings.hpp"

#include "cstdio"

#ifdef DEBUG
    #define LOGS(...) printf(__VA_ARGS__);
#else
    #define LOGS(data, ...) ;
#endif

/*
template <typename T>
struct privDefer {
	T f;
	privDefer(T f) : f(f) {
		LOGS("INFO >>> defered function coustructed\n")
	}
	~privDefer() { 
		f(); 
		LOGS("INFO >>> defered function destructed\n")
	}
};

template <typename T>
privDefer<T> defer_func(T f) {
	return privDefer<T>(f);
}

#define DEFER_1(x, y) x##y
#define DEFER_2(x, y) DEFER_1(x, y)
#define DEFER_3(x)    DEFER_2(x, __COUNTER__)
#define defer(code)   auto DEFER_3(_defer_) = defer_func([&](){code;})
*/

#define NON_COPYBLE(className)\
    className(const className&) = delete;\
    className& operator=(const className&) = delete;