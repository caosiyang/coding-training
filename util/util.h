#pragma once

#include <time.h>
#include <string>
#include <sstream>

class Timer {
public:
    static void Start() {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);
    }

    static void End() {
        clock_gettime(CLOCK_MONOTONIC, &ts_end);
    }

    static std::string Delta() {
        float n = float((ts_end.tv_sec * 1000000000 + ts_end.tv_nsec) - (ts_start.tv_sec * 1000000000 + ts_start.tv_nsec)) / 1000000;
        std::stringstream ss;
        ss << n << " ms";
        return ss.str();
    }

private:
    static struct timespec ts_start;
    static struct timespec ts_end;
};

struct timespec Timer::ts_start = {0, 0};
struct timespec Timer::ts_end = {0, 0};

// ascending order
template <typename T>
int asc(T a, T b) {
    if (a > b) {
        return 1;
    } else if (a < b) {
        return -1;
    } else {
        return 0;
    }
}

// descending order
template <typename T>
int desc(T a, T b) {
    if (a > b) {
        return -1;
    } else if (a < b) {
        return 1;
    } else {
        return 0;
    }
}

template <typename T>
bool valid(T *start, T *end, int (*cmp)(T a, T b)) {
    int *p = start;
    while (p < end) {
        if (cmp(*(p + 1), *p) < 0) {
            return false;
        }
        ++p;
    }
    return true;
}

template <typename T>
std::string output(const T *start, int count) {
    std::stringstream ss;
    ss << "[ ";
    for (int i = 0; i < count; ++i) {
        ss << *(start + i) << " ";
    }
    ss << "]";
    return ss.str();
}
