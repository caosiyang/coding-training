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
